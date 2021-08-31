#include <iostream>
#include <string>

using namespace std;

template<typename V>
class MapNode{
public:
    string key;
    V value;
    MapNode *next;

    MapNode(string key, V value){
        this->key = key;
        this->value = value;
        next = NULL;
    }

    ~MapNode(){
        delete next;
    }
};

/// un map implementat cu Separate Chaining, adica unde doua chei rezulta acelasi index in map dupa ce se aplica
/// functia de Hash, vor fi puse de fapt intr-un linked list, al carui head este salvat de fapt la adresa de la indicele acela
template<typename V>
class MyMap{
    ///un vector de celule(noduri) din map, unde fiecare nod e Head-ul unei linked list plina cu iteme care au aceeasi cheie
    MapNode<V>* *buckets;
    ///count e numarul de elemente din fiecare linked list adunate. adica toate elementele din Map
    int count;
    ///numarul de noduri din buckets
    int numBuckets;

    ///functia getBucketIndex e hash function-ul
    int getBucketIndex(string key){
        int hashCode = 0;

        ///p e nr prim dupa care facem functia de hash
        int base = 1;
        int p = 37;
        for(int i=key.size()-1;i>=0;i--){
            hashCode += key[i] * base;
            base = base * p;

            /// asta e pentru a pastra val;orile in range de int, caci indexul final va fo tot acelasi, ca foloseste %
            hashCode = hashCode % numBuckets;
            base = base%numBuckets;
        }

        ///la final practic fac compresia dupa numarul de celule din map.
        return hashCode%numBuckets;
    }

    void rehash(){
        /// fac un nou vector temporar de marime dubla, pun valori null in el
        MapNode<V>* *temp = buckets;
        buckets = new MapNode<V>*[2*numBuckets];
        for(int i=0;i<numBuckets*2;i++){
            buckets[i] = NULL;
        }
        /// reinitializez variabilele
        int oldNumBuckets =  numBuckets;
        count = 0;
        numBuckets = numBuckets * 2;

        for(int i=0;i<oldNumBuckets;i++){
            MapNode<V>* head = temp[i];
            while(head != NULL){
                string key = head->key;
                V value = head -> value;
                insert(key, value);
                head = head->next;
            }
        }
        /// stergem mai intai linked list-urile care se sterg cu totul apoi la final sterg si vectorul Temp, adica buckets vechi
        for(int i=0; i< oldNumBuckets; i++){
            delete temp[i];
        }
        delete []temp;
    }

public:
    MyMap(){
        count = 0;
        numBuckets = 5;
        buckets = new MapNode<V>*[numBuckets];
        //initial, vectorul buckets are garbage values dar le fac null pe toate
        for(int i=0;i<numBuckets;i++){
            buckets[i] = NULL;
        }
    }

    ~MyMap(){
        for(int i=0;i<numBuckets;i++){
            delete buckets[i];
        }
        delete []buckets;
    }

    int size(){
        return count;
    }

    ///functie care cauta o valoare in map
    V getValue(string key){
        int bucketIndex = getBucketIndex(key);
        MapNode<V>* head = buckets[bucketIndex];
        while(head!=NULL){
            if(head->key == key){
                return head->value;
            }
            head = head->next;
        }
        /// 0 inseamna ca valoarea nu exista in map;
        return 0;
    }

    /// time complexity: O(n/b), worst case cand toate entries sunt la acelasi index, deci trb parcurs LL-ul cu totul deci O(n)
    /// functia de hash are time complexity mult mai mic decat nr de entries, putem presupune direct O(1)
    /// O(n/b)< 0.7 = load factor, unde b e nr de buckets, adica celule din map, adica nr de linked lists.
    /// deci on average, complexity O(<1) deci O(1)
    void insert(string key, V value){
        int bucketIndex = getBucketIndex(key);

        ///iau capul listei si o parcurg sa vad daca exista deja pereceha (key,value)
        MapNode<V>* head = buckets[bucketIndex];
        while(head!=NULL){
            if(head->key == key){
                head->value = value;
                return;
            }
            head= head->next;
        }
        /// daca nu am gasit cheia in LL-ul acela, o adaugam
        MapNode<V>* node = new MapNode<V>(key, value);
        node->next = buckets[bucketIndex];
        buckets[bucketIndex] = node;
        count++;

        /// calculez acest load factor pentru a il mentine sub 0.7. daca e peste, vom face rehashing, adica luam
        /// toate elementele si le trecem iar prin functia de hash dar intr-un map cu numar dublu de buckets.
        double loadFactor = (1.0*count)/numBuckets;
        if(loadFactor > 0.7){
            rehash();
        }
    }

    ///functia remove elimina item-ul acela si returneaza valoarea pe care o avea
    V remove(string key){
        int bucketIndex = getBucketIndex(key);
        MapNode<V>* head = buckets[bucketIndex];
        MapNode<V>* prev = NULL;
        while(head!=NULL){
            if(head->key==key){
                if(prev == NULL){
                    buckets[bucketIndex] = head->next;
                }
                else{
                    prev->next = head->next;
                }
                V value = head->value;
                head->next = NULL;
                delete head;
                count--;
                return value;
            }

            prev = head;
            head = head->next;
        }
        /// 0 inseamna ca valoarea nu exista in map;
        return 0;
    }

    double getLoadFactor(){
        return (1.0* count) / numBuckets;
    }
};

int main() {
    MyMap<int> mymap;
    for(int i = 0; i <10; i++){
        /// introduc in map valori cu chei de genul "abc1":1  "abc2":2  "abc3":3 ....
        char c = '0' + i;
        string key = "abc";
        key = key + c;
        int value = i+1;
        mymap.insert(key, value);
        cout<<mymap.getLoadFactor()<<endl;
        /// cand insereaza al 4-lea element, loadFactor-ul ar fi 4/5, asa ca va face rehashing.
    }

    cout<<mymap.size()<<endl;

    mymap.remove("abc1");
    mymap.remove("abc4");
    for(int i = 0; i <10; i++){
        char c = '0' + i;
        string key = "abc";
        key = key + c;
        cout<<key<<" "<<mymap.getValue(key)<<endl;
    }
    cout<<mymap.size()<<endl;
}
