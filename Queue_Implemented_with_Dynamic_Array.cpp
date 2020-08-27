#include <iostream>

using namespace std;

template <typename T>
class Queue{
    T *arr;
    int nextIndex;
    int firstIndex;
    int size;
    int capacity;
public:
    Queue(){
        capacity=5;
        arr=new T[capacity];
        nextIndex=0;
        firstIndex=-1;
        size=0;
    }
    Queue(int cap){
        capacity=cap;
        arr=new T[capacity];
        nextIndex=0;
        firstIndex=-1;
        size=0;
    }
    int getSize(){
        return size;
    }
    bool isEmpty(){
        return size==0;
    }
    void push(T element){
        if(size==capacity){
            T *newArr= new T[capacity*2];
            int j=0;
            for(int i=firstIndex;i<=capacity-1;i++) {
                newArr[j] = arr[i];
                j++;
            }
            for(int i=0;i<=firstIndex-1;i++){
                newArr[j] = arr[i];
                j++;
            }
            firstIndex=0;
            nextIndex=capacity;
            capacity=capacity*2;
            delete []arr;
            arr=newArr;
        }
        arr[nextIndex]=element;
        nextIndex=(nextIndex+1)%capacity;
        if(firstIndex==-1)
            firstIndex=0;
        size++;
    }
    T front(){
        if(isEmpty()) {
            cout << "Queue empty" << endl;
            return 0;
        }
        return arr[firstIndex];
    }
    void pop(){
        if(isEmpty()){
            cout<<"Queue empty"<<endl;
            return;
        }
        firstIndex=(firstIndex+1)%capacity;
        size--;
        ///reset variabilele
        if(size==0){
            nextIndex=0;
            firstIndex=-1;
        }
    }
};
int main() {
    Queue<int> q(5);

    q.push(10);
    q.push(20);
    q.push(30);
    q.push(40);
    q.push(50);
    q.push(60);
    q.push(70);
    cout<<q.getSize()<<endl;


    cout<<q.front()<<endl;
    q.pop();
    q.pop();
    cout<<q.getSize()<<endl;

    cout<<q.front()<<endl;
    q.pop();

    cout<<q.isEmpty()<<endl;
    cout<<q.getSize()<<endl;
    q.push(100);
    q.push(200);
    q.push(300);

    cout<<q.front()<<endl;
    cout<<q.getSize()<<endl;

}
