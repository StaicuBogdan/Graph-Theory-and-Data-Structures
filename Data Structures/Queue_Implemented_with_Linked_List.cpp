#include <iostream>

using namespace std;

template <typename T>
class Node{
public:
    T data;
    Node<T> *next;
    Node(T data){
        this->data=data;
        next=NULL;
    }
};
template <typename T>
class Queue{
    Node<T> *head;
    Node<T> *tail;
    int size;
public:
    Queue(){
        size=0;
        head=NULL;
        tail=NULL;
    }
    int getSize(){
        return size;
    }
    bool isEmpty(){
        return size==0;
    }
    void push(T element){
        Node<T> *n=new Node<T>(element);
        if(isEmpty()){
            head=n;
            tail=n;
        }
        tail->next=n;
        tail=n;
        size++;
    }
    T front(){
        if(!isEmpty())
            return head->data;
        cout<<"Queue empty"<<endl;
        return 0;
    }
    void pop(){
        if(isEmpty()){
            cout<<"Queue empty"<<endl;
            return;
        }
        Node<T> *temp=head->next;
        delete head;
        head=temp;
        size--;
    }

};
int main() {
    Queue<int> q;

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
