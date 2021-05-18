#include <iostream>

using namespace std;

template<typename T>
class Node {
public:
    T data;
    Node *next;
    Node(T data) {
        this->data = data;
        next = NULL;
    }
    /*
    T getData(){
        return data;
    }
    Node* getNext(){
        return next;
    }
    void setData(T dataVal){
        this->data=data;
    }
    void setNext(Node *nextVal){
        this->next=next;
    }
    */
};

template<typename T>
class Stack {
    Node<T> *head;
    int size;
public:
    Stack() {
        head = NULL;
        size = 0;
    }

    int getSize() {
        return size;
    }

    bool isEmpty() {
        return size==0;
    }

    void push(T data) {
        Node<T> *n = new Node<T>(data);
        n->next = head;
        head = n;
        size++;
    }

    void pop() {
        if (isEmpty()){
            cout<<"stack empty"<<endl;
            return;
        }
        Node<T> *temp = head;
        head = head->next;
        temp->next=NULL;
        delete temp;
        size--;
    }

    T top() {
        if (isEmpty()){
            cout<<"stack empty"<<endl;
            return 0;
        }
        return head->data;
    }

};

int main() {
    Stack<char> s;
    s.push(100);
    s.push(101);
    s.push(102);
    s.push(103);
    s.push(104);

    cout<<s.top()<<endl;
    s.pop();

    cout<<s.top()<<endl;
    s.pop();

    cout<<s.top()<<endl;
    s.pop();

    cout<<s.getSize()<<endl;

    cout<<s.isEmpty()<<endl;

    Stack<int> s2;
    s2.push(100);
    s2.push(101);
    s2.push(102);
    s2.push(103);
    s2.push(104);

    cout<<s2.top()<<endl;
    s2.pop();

    cout<<s2.top()<<endl;
    s2.pop();

    cout<<s2.top()<<endl;
    s2.pop();

    cout<<s2.getSize()<<endl;

    cout<<s2.isEmpty()<<endl;

}
