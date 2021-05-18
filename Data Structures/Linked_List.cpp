#include <iostream>

using namespace std;

class Node {
public:
    int data;
    Node *next;

    explicit Node(int data) {
        this->data = data;
        next = NULL;
    }
};

void print(Node *head) {
    while (head != NULL) {
        cout << head->data << " ";
        head = head->next;
    }
    cout << endl;
}

Node *input() {
    int data;
    cin >> data;
    Node *head = NULL;
    Node *tail = NULL;
    ///inserare la coada
    while (data != -1) {
        Node *n = new Node(data);
        if (head == NULL) {
            head = n;
            tail = n;
        } else {
            tail->next = n;
            tail = n;
        }
        cin >> data;
    }
    ///inserare la cap
    /*
    while (data != -1) {
        Node *n = new Node(data);
        if (head == NULL) {
            head = n;
            tail = n;
        } else {
            n->next=head;
            head = n;
        }
        cin >> data;
    }
     */
    return head;
}

int length(Node *head) {
    int l = 0;
    while (head != NULL) {
        l++;
        head = head->next;
    }
    return l;
}

int lengthRecursive(Node *head) {
    if (head == NULL)
        return 0;
    else
        return 1 + lengthRecursive(head->next);
}

void printKNode(Node *head, int k) {
    if (k < 0) {
        cout << "-1" << endl;
        return;
    }
    while (k) {
        head = head->next;
        k--;
    }
    if (head)
        cout << head->data << endl;
    else
        cout << "-1" << endl;
}

Node *insertKPosition(Node *head, int k, int data) {
    ///daca e indicele inexistent
    if (k < 0)
        return head;
    ///daca e primul element din lista
    if (k == 0) {
        Node *temp = head;
        temp->next = head;
        head = temp;
        return head;
    }
    ///ii facem o copie pentru a reveni la final
    Node *copieHead = head;
    while (k > 1) {
        head = head->next;
        k--;
    }
    ///cream un nod nou si facem legaturile intre el si cele 2 noduri adiacente
    if (head) {
        Node *n = new Node(data);
        n->next = head->next;
        head->next = n;
    }
    head = copieHead;
    return head;
}

Node *deleteKPosition(Node *head, int k) {
    ///daca e indicele inexistent
    if (k < 0 || k >= length(head))
        return head;
    ///daca e primul element de eliminat din lista
    if (k == 0 && head) {
        //return head->next; cu memory leak
        Node *newHead = head->next;
        head->next = NULL;
        delete head;
        return newHead;
    }
    ///facem o copie la capul listei
    Node *copieHead = head;
    ///parcurgem lista pana la elementul care trebuie eliminat
    while (k > 1) {
        head = head->next;
        k--;
    }
    ///daca nu trebuie eliminat ultimul element din lista o sa intre in if-ul acesta si va elimina elementul care trebuie
    if (head && head->next) {
        Node *temp = head->next;
        head->next = head->next->next;
        temp->next = NULL;
        delete temp;
    }
    head = copieHead;
    return head;
}

bool existaElement(Node *head, int x) {
    while (head) {
        if (head->data == x)
            return true;
        head = head->next;
    }
    return false;
}

bool existaElementRecursiv(Node *head, int x) {
    if (head->data == x)
        return true;
    else if (head->next)
        return existaElementRecursiv(head->next, x);
    else
        return false;
}

Node *mijloculListei(Node *head) {
    Node *fastPointer = head->next;
    Node *slowPointer = head;
    while (fastPointer != NULL && fastPointer->next != NULL) {
        fastPointer = fastPointer->next->next;
        slowPointer = slowPointer->next;
    }
    if (fastPointer == NULL)
        return slowPointer;
    if (fastPointer->next == NULL)
        return slowPointer->next;
}

Node *reverseList(Node *head) {
    Node *previous = head;
    Node *current = head->next;
    Node *n = current->next;
    ///previous va fo noua coada a listei, deci NULL
    previous->next = NULL;
    while (n != NULL) {
        current->next = previous;
        previous = current;
        current = n;
        n = n->next;
    }
    current->next = previous;
    return current;
}

Node *eliminaKNodDinCoada(Node *head, int k) {
    Node *copieHead = head;
    int l = length(head);
    //cout<<"Lungimea listei:"<<l<<endl;
    if (k > l || k < 0)
        return head;
    ///daca e primul nod din cap adina al n-lea din coada
    if (k == l) {
        Node *temp = head;
        head = head->next;
        delete temp;
        return head;
    }
    ///ducem head pana la nodul din fata celui care trebuie eliminat si il eliminam
    for (int i = 0; i < l - k - 1; i++)
        head = head->next;
    Node *temp = head->next;
    head->next = head->next->next;
    delete temp;
    head = copieHead;
    return head;

};

Node *interclasare(Node *head1, Node *head2) {
    if (head1 == NULL)
        return head2;
    if (head2 == NULL)
        return head1;
    Node *finalHead, *finalTail;
    if (head1->data < head2->data) {
        finalHead = head1;
        finalTail = head1;
        head1 = head1->next;
    } else {
        finalHead = head2;
        finalTail = head2;
        head2 = head2->next;
    }
    while (head1 && head2) {
        if (head1->data <= head2->data) {
            finalTail->next = head1;
            finalTail = head1;
            head1 = head1->next;
        } else {
            finalTail->next = head2;
            finalTail = head2;
            head2 = head2->next;
        }
    }
    if (head1 == NULL)
        finalTail->next = head2;
    if (head2 == NULL)
        finalTail->next = head1;

    return finalHead;
}

int main() {
    /*
    Node n1(10);
    Node n2(20);
    Node n3(30);
    Node n4(40);

    Node *head=&n1;

    n1.next=&n2;
    n2.next=&n3;
    n3.next=&n4;

    print(head);


    Node *n1 = new Node(100);
    Node *n2 = new Node(200);
    Node *n3 = new Node(300);
    Node *n4 = new Node(400);
    Node *n5 = new Node(500);

    Node *head = n1;

    n1->next = n2;
    n2->next = n3;
    n3->next = n4;
    n4->next = n5;

    print(head);
    */
    Node *listaMea = input();

    ///Node *listaMeaInversa = input();
    print(listaMea);
    cout << endl;
    //cout<<"Lungimea listei este:"<<length(listaMea)<<endl;
    //cout<<"Nodul nr 3 este:";

    //printKNode(listaMea, 1);
    //insertKPosition(listaMea,3,1000);
    //deleteKPosition(listaMea,2);

    //print(listaMea);
    //cout<<lengthRecursive(listaMea)<<endl;

    //cout<<existaElement(listaMea, 5)<<endl;
    //cout<<existaElementRecursiv(listaMea, 5)<<endl;

    //Node *mijloc = mijloculListei(listaMea);
    //cout<<"Mijlocul listei este:"<< mijloc->data<<endl;

    //listaMea=reverseList(listaMea);
    //print(listaMea);

    //listaMea=eliminaKNodDinCoada(listaMea, 1);
    //print(listaMea);

    Node *listaMea2 = input();
    listaMea = interclasare(listaMea, listaMea2);
    print(listaMea);

}
