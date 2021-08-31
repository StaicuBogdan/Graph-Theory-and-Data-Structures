#include <iostream>
#include <unordered_map>
#include <string>
#include <vector>

using namespace std;

vector<int> removeDuplicates(int *array, int size){
    vector<int> output;
    unordered_map<int, bool> mymap;

    for(int i=0; i<=size-1;i++){
        if(mymap.count(array[i])==0){
            output.push_back(array[i]);
            mymap[array[i]]= true;
        }
    }
    return output;
}

int main() {
    /*
    unordered_map<string, int> mymap;

    ///insert
    pair<string, int> p("abc", 1);
    mymap.insert(p);


    ///access or find
    mymap["def"] = 2; //like array


    cout<<"def: "<<mymap["def"]<<endl;
    cout<<"abc: "<<mymap.at("abc")<<endl;

    cout<<"Size:"<<mymap.size()<<endl;

    //cout<< mymap.at("ghi") // exception, key not found
    //daca cheia nu exista, iar eu accesez ca pe vector, o baga el cu valoarea zero
    cout<<"ghi: "<<mymap["ghi"]<<endl;
    cout<<"Size:"<<mymap.size()<<endl;


    ///check if a key is present
    if(mymap.count("ghi")>0)
        cout<<"Cheia exista"<<endl;
    else
        cout<<"cheia nu exista"<<endl;


    ///update value
    mymap["abc"] = 20;
    cout<<"abc: "<<mymap.at("abc")<<endl;


    ///erase value
    mymap.erase("ghi");
    cout<<"Size:"<<mymap.size()<<endl;
    if(mymap.count("ghi")>0)
        cout<<"Cheia exista"<<endl;
    else
        cout<<"cheia nu exista"<<endl;

    cout<<mymap.count("abc")<<endl;*/

    int v[] = {1,5,2,4,4,3,3,6,7,1,1,2};
    vector<int> output = removeDuplicates(v, 12);

    for(int i=0; i<output.size();i++)
        cout<<output[i]<<" ";
}
