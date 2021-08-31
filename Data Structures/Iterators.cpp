#include <iostream>
#include <unordered_map>
#include <map>
#include <vector>

using namespace std;

int main() {
    unordered_map<string, int> mymap;
    mymap["abc"] = 1;
    mymap["abc1"] = 2;
    mymap["abc2"] = 3;
    mymap["abc3"] = 4;
    mymap["abc4"] = 5;
    mymap["abc5"] = 6;

    for(unordered_map<string, int>::iterator it = mymap.begin(); it!=mymap.end(); it++){
        cout<<"Key: "<<it->first<<" Value: "<<it->second<<endl;
    }

    cout<<"-----------------"<<endl;

    map<string, int> mymap2;
    mymap2["abc1"] = 2;
    mymap2["abc"] = 10;
    mymap2["abc2"] = 3;
    mymap2["abc3"] = 4;
    mymap2["abc4"] = 5;
    mymap2["abc5"] = 6;

    /// MAP SORTS BASED ON KEYS, NOT ON VALUES
    for(auto & it : mymap2){
        cout<<"Key: "<<it.first<<" Value: "<<it.second<<endl;
    }

    cout<<"-----------------"<<endl;
    vector<int> v;
    v.push_back(10);
    v.push_back(2);
    v.push_back(3);
    v.push_back(4);
    v.push_back(5);

    for(vector<int>::iterator it = v.begin(); it != v.end(); it++){
        cout<<*it<<endl;
    }

    //unordered_map<string, int>::iterator it =  mymap.find("abc");
    /// erase poate primi ca valoare o cheie sau un iterator. Poate primi si 2 parametri: start iterator si end iterator
    /// erase(it, it+4) sterge pana la al doilea exclusiv, gen python. Asta nu merge pe chestii unordered ca nu stie care e next element
    /// erase(mymap.begin(), mymap.end()) va sterge tot ce e in mymap de exemplu
    mymap.erase(mymap.begin(), mymap.end());

    /// find element: functie care primeste o cheie si returneaza un iterator
    /// mymap.end() practic e un iterator care pointeaza in afara map-ului, dupa ce s-a terminat de parcurs
    /// deci practic conditia va fi falsa daca il gaseste in mymap pe "abc", true doar daca ajune la capat
    ///  |_|_|_|_|_|_|_| end <-
    if(mymap.find("abc") == mymap.end()){
        cout<<"Not present!"<<endl;
    }
    else{
        cout<<"Present!"<<endl;
    }

    /// unordered_map<string, int>::iterator e un Datatype, deco pot scrie si auto in loc de asta
    // output gol
    for(auto it = mymap.begin(); it!=mymap.end(); it++){
        cout<<"Key: "<<it->first<<" Value: "<<it->second<<endl;
    }

    cout<<mymap.size()<<endl;

    auto a = 5;
    cout<<a<<endl;
    auto b = "abcd";
    cout<<b<<endl;
}
