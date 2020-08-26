#include <iostream>

using namespace std;

template <typename T>
class Stack{
    T *v;
    int nextIndex;
    int capacity;
public:
    Stack(){
        capacity=4;
        v= new T[capacity];
        nextIndex=0;
    }
    int size(){
        return nextIndex;
    }
    bool isEmpty(){
        return nextIndex == 0;
    }
    void push(T data){
        if(capacity==nextIndex) {
            T *vDouble= new T[capacity*2];
            for(int i=0;i<=nextIndex-1;i++)
                vDouble[i]=v[i];
            delete []v;
            v=vDouble;
            capacity=capacity*2;
        }
        v[nextIndex] = data;
        nextIndex++;
    }
    void pop(){
        if(isEmpty()) {
            cout << "stack empty" << endl;
            return;
        }
        else
            nextIndex--;
    }
    T top(){
        if(!isEmpty())
            return v[nextIndex-1];
        else {
            cout << "stack empty" << endl;
            return 0;
        }
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

    cout<<s.size()<<endl;

    cout<<s.isEmpty()<<endl;
    /*
    Stack s2;
    for(int i=1;i<=10;i++)
        s2.push(i);

    while(!s2.isEmpty()) {
        cout << s2.top()<<" ";
        s2.pop();
    }

    cout<<s2.size()<<endl;
*/
}
