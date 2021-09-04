#include <iostream>
#include <vector>
#include <queue>
using namespace std;

/// Heap-ul este o structura de date care ajuta la implementarea unui Priority Queue
/// Are 2 proprietati: Este Complete Binary Tree (CBT) si are Heap Order Property (parintele preceda copiii intotdeauna)
/// Pentru Min-Heap, parintele<copiii, pentru Max-Heap, parintele>copiii
/// Este un CBT implementat cu un simplu array, pentru care voi retine 2 formule de ordonare a elementelor dupa indici
/// 1. Pentru elementul de la indicele i, cei 2 copii sunt la indicii 2i+1 si 2i+2
/// 2. Pentru orice indice, indicele parintelui este (i-1)/2

/// Inaltimea unui CBT este mereu h=log(n)

/// Min-Heap / Min-PQ : getMin() -> O(1),      removeMin() -> O(h) = O(logN) worst case pentru ca trebuie facut Down-Heapify.
///                      insert() -> O(h) = O(logN) worst case pentru ca trebuie facut Up-Heapify.
/// la fel si pentru Max-Heap / Max-PQ

/// Heap Sort: iau N elemente si le inserez in heap, apoi le scot, deci HeapSort are complexitate 2NlogN ~ O(NlogN)

class PriorityQueue{
    vector<int> pq;
public:
    PriorityQueue(){}

    bool isEmpty(){
        return pq.empty();
    }

    /// Return total number of elements present
    int getSize(){
        return pq.size();
    }

    int getMin(){
        if(isEmpty()){
            /// 0 inseamna ca nu e niciun element in pq
            return 0;
        }
        return pq.at(0);
    }

    void insert(int elem){
        pq.push_back(elem); /// cat timp doar inserez ramane cbt, dar trb verificat si proprietatea de Heap Order acum
        int cI = pq.size() -1; /// indicele ultimului element inserat (childIndex)

        /// while-ul asta e Up-Heapify
        while(cI > 0){
            int pI = (cI - 1)/2; /// parent index
            if(pq[cI] < pq[pI]){
                swap(pq[cI], pq[pI]);
                cI = pI;
            }
            else{
                break;
            }
        }
    }

    int removeMin(){
        if(isEmpty()){
            return 0;
        }
        int ans = pq[0];
        /// inlocuiesc mai intei primul element cu ultimul
        swap(pq[0], pq[pq.size()-1]);
        pq.pop_back();

        /// apoi fac Down-Heapify;
        int pI = 0;
        while(true){
            int lcI = 2*pI + 1, rcI = 2*pI + 2;
            int minIndex = pI;

            if(lcI < pq.size() && pq[lcI]< pq[minIndex]){
                minIndex = lcI;
            }
            if(rcI < pq.size() && pq[rcI] < pq[minIndex]){
                minIndex = rcI;
            }

            if(minIndex == pI){
                break;
            }

            swap(pq[pI], pq[minIndex]);
            pI = minIndex;
        }
        return ans;
    }
};


/// pentru Inplace Heap Sort, nu voi mai crea un heap nou, ci doar primesc ca parametru un vector de elemente si
/// aplic Up-Heapify pe elementele lui 1 cate 1, pana cand vectorul arata ca un Heap, apoi le scot cu functia removeMin
/// putin modificata, caci nu scoate niciun element din vector, doar presupune ca unele sunt eliminate cu ajutorul unei
/// variabile Size
/// Complexitate Timp tot O(NlogN), dar Space Complexity mai bun, caci nu mai creez un heap nou
/// Min-Heap -> Vector sortat descrescator,  Max-Heap -> vector sortat crescator
void inplaceHeapSort(int *pq, int n){
    /// Build heap inside the input array
    /// primul element e considerat deja in heap, deci incepem for-ul de la 1
    for(int i = 1; i<n;i++){
        ///doar fac direct Up-Heapify
        int cI = i;
        while(cI > 0){
            int pI = (cI - 1)/2; /// parent index
            if(pq[cI] < pq[pI]){
                swap(pq[cI], pq[pI]);
                cI = pI;
            }
            else{
                break;
            }
        }
    }

    /// removeMin de N ori
    int size = n;
    while(size>=1){
        swap(pq[0],pq[size-1]);
        size--; /// elementul a fost "eliminat"

        /// Down-Heapify
        int pI = 0;
        while(true){
            int lcI = 2*pI + 1, rcI = 2*pI + 2;
            int minIndex = pI;

            if(lcI < size && pq[lcI]< pq[minIndex]){
                minIndex = lcI;
            }
            if(rcI < size && pq[rcI] < pq[minIndex]){
                minIndex = rcI;
            }

            if(minIndex == pI){
                break;
            }

            swap(pq[pI], pq[minIndex]);
            pI = minIndex;
        }
    }
}

/// Time complexity: primul for si while-ul au complexitate KlogK , iar al 2-lea for are complexitate (N-K)logK
/// deci Complexitate O(NlogK) adica O(N) liniar. Space complexity O(k) de la PQ, deci O(1)
void kSortedArray(int *input, int n, int k){
    priority_queue<int> pq;

    /// inserez primele k elemente in priority queue
    for(int i=0;i<k;i++){
        pq.push(input[i]);
    }

    ///s e indicele de start unde va trebui pus element prima data
    int s = 0;
    for(int i=k;i<n;i++){
        /// la indicele s punem elementul maxim din pq (adica din primele k elemente inserate in pq)
        input[s] = pq.top();
        /// apoi il scoatem din pq
        pq.pop();
        /// trecem la indicele urmator
        s++;
        /// bagam apoi elementul i in pq, adica urmatorul element, care e la pozitia k in vector, ca de acolo incepe for-ul
        pq.push(input[i]);
    }

    /// din moment ce for-ul de mai sus merge pana la n, cand se termina mai raman k elemente in pq, si le sortam si pe acelea
    while(!pq.empty()){
        input[s] = pq.top();
        pq.pop();
        s++;
    }
}

/// Functia foloseste un PQ cu primele k elemente, apoi parcurge vectorul de la pozitia k incolo si de fiecare data cand
/// gasesc un element mai mic decat PQ.top(), adica varful max-heap-ului, il scot si inserez acel element, astfel in
/// PQ raman cele k cele mai mici elemente din vector
/// Time complexity: O(NlogK)
void kSmallestElements(int *arr, int n, int k){
    priority_queue<int> pq;
    /*
    for(int i=0;i<k;i++){
        pq.push(arr[i]);
    }

    for(int i=k;i<n;i++){
        if(arr[i]<pq.top()){
            pq.pop();
            pq.push(arr[i]);
        }
    }
     */
    /// varianta simplificata, unde elimin varful heap-ului in acelasi for in care inserez elementele in pq
    for(int i=0;i<n;i++){
        pq.push(arr[i]);
        if(pq.size()>k){
            pq.pop();
        }
    }

    ///rezultatul
    while(!pq.empty()){
        cout<<pq.top()<<" ";
        pq.pop();
    }
}

void kSmallestElementsMinHeap(int *arr, int n, int k){
    /// daca inserez cu un for, time complexity este O(NlogN)
    /*
    priority_queue<int, vector<int>, greater<>> pq; /// min pq
    for(int i=0;i<n;i++){
        pq.push(arr[i]);
    }
    */
    priority_queue<int, vector<int>, greater<>> pq(arr, arr+n); /// O(n)
    /// daca foloseam vector, in loc de arr si arr+n, foloseam v.begin() si v.end()

    /// pop k elements
    for(int i =1;i<=k;i++){
        cout<<pq.top()<<" ";
        pq.pop();
    }
}

/// la fel ca kSmallestElements, dar folosesc un Min-Heap
void kLargestElements(int *arr, int n, int k){
    priority_queue<int, vector<int>, greater<>> pq; /// O(n)

    for(int i=0;i<n;i++){
        pq.push(arr[i]);
        if(pq.size()>k){
            pq.pop();
        }
    }
    while(!pq.empty()){
        cout<<pq.top()<<" ";
        pq.pop();
    }
}

void kLargestElementsMaxHeap(int *arr, int n, int k){
    priority_queue<int> pq(arr, arr+n); /// O(n)
    /// daca foloseam vector, in loc de arr si arr+n, foloseam v.begin() si v.end()

    /// pop k elements
    for(int i =1;i<=k;i++){
        cout<<pq.top()<<" ";
        pq.pop();
    }
}

int main() {
    PriorityQueue p;
    p.insert(100);
    p.insert(10);
    p.insert(15);
    p.insert(4);
    p.insert(17);
    p.insert(21);
    p.insert(67);
    p.insert(1);

    cout<<"Size: "<<p.getSize()<<endl;
    cout<<"Min element: "<<p.getMin()<<endl;

    while(!p.isEmpty()){
        cout<<p.removeMin()<<" ";
    }
    cout<<endl;

    int input[] = {5,1,2,0,8};
    inplaceHeapSort(input, 5);

    for(int i : input)
        cout<<i<<" ";
    cout<<endl;cout<<endl;

    /// -------------------------------------------

    /// Inbuilt PQ uses Max-Heap
    cout<<"Inbuilt PQ:"<<endl;
    priority_queue<int> pq;
    pq.push(16);
    pq.push(1);
    pq.push(167);
    pq.push(7);
    pq.push(45);
    pq.push(32);
    pq.push(100);

    cout<<"Size: "<<pq.size()<<endl;
    cout<<"Top element: "<<pq.top()<<endl;

    while(!pq.empty()){
        cout<<pq.top()<<" ";
        pq.pop();
    }
    cout<<endl;cout<<endl;

    /// -------------------------------------------

    /// Inbuilt PQ that uses Min-Heap
    cout<<"Inbuilt Min-Heap PQ:"<<endl;
    priority_queue<int, vector<int>, greater<>> pq2;
    pq2.push(16);
    pq2.push(1);
    pq2.push(167);
    pq2.push(7);
    pq2.push(45);
    pq2.push(32);
    pq2.push(100);

    cout<<"Size: "<<pq2.size()<<endl;
    cout<<"Top element: "<<pq2.top()<<endl;

    while(!pq2.empty()){
        cout<<pq2.top()<<" ";
        pq2.pop();
    }
    cout<<endl;cout<<endl;

    /// -------------------------------------------

    cout<<"K Sorted Array (k=3):"<<endl;
    int kArray[] = {10, 12, 6, 7, 9};
    int k = 3;
    kSortedArray(kArray,5,k);

    for(int i : kArray){
        cout<<i<<" ";
    }
    cout<<endl;cout<<endl;

    /// -------------------------------------------

    cout<<"K Smallest elemets (k=3):"<<endl;
    int kSmallest[] = {5, 6, 9, 12, 3, 13, 2};
    cout<<"Max-Heap: ";
    kSmallestElements(kSmallest, 7, 3);
    cout<<endl;
    cout<<"Min-Heap: ";
    kSmallestElementsMinHeap(kSmallest, 7, 3);
    cout<<endl;cout<<endl;

    /// -------------------------------------------

    cout<<"K Largest elemets (k=3):"<<endl;
    int kLargest[] = {5, 6, 9, 12, 3, 13, 2};
    cout<<"Min-Heap: ";
    kLargestElements(kLargest, 7, 3);
    cout<<endl;
    cout<<"Max-Heap: ";
    kLargestElementsMaxHeap(kLargest, 7, 3);
    return 0;

}

