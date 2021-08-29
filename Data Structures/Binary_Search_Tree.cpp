#include <iostream>
#include <queue>
#include <vector>

using namespace std;

/// clasa pentru un nod de Binary Tree
template <typename T>
class BTNode{
public:
    T data;
    BTNode *left;
    BTNode *right;

    BTNode(T data){
        this->data=data;
        left=NULL;
        right=NULL;
    }

    ~BTNode(){
        delete left;
        delete right;
    }
};

class Pair{
public:
    BTNode<int> *head;
    BTNode<int> *tail;
};

///clasa pentru BST-ul propriu-zis
class BST{
    BTNode<int> *root;

    BTNode<int>* deleteData(BTNode<int> *node, int data){
        if(node == NULL)
            return NULL;

        ///mai intai ajungem la nod, iar apoi modificam arborele cum trebuie
        if(node->data < data){
            node->right = deleteData(node->right, data);
        }
        else if(data < node->data){
            node->left = deleteData(node->left, data);
        } else{
            ///am gasit nodul pe care vreau sa il sterg, aici avem 3 cazuri
            ///1. Daca nodul e frunza
            if(node->left == NULL && node->right == NULL){
                ///il stergem si doar returnez NULL ca sa updateze recursia mai sus ca parintele are nodul copil NULL
                delete node;
                return NULL;
            }
            else if(node->right == NULL){
                ///2a. cand are doar subarbore stanga, iar in dreapta NULL
                ///Deoarece destructorul e recursiv, mai intai salvam subarborele stanga in variabila temp, apoi
                /// izolam subarborele, adica fac nodul sa nu mai pointeze catre subarbore, apoi pot sterge
                BTNode<int> *temp = node->left;
                node->left = NULL;
                delete node;
                return temp;
            }
            else if(node->left == NULL){
                ///2b. La fel ca 2a. doar ca pentru celalalt subarbore
                BTNode<int> *temp = node->right;
                node->right = NULL;
                delete node;
                return temp;
            }
            else{
                ///3. Cand exista ambii subarbori. Trick: putem inlocui nodul de eliminat ori cu nodul LeftMax sau cu
                /// RightMin. numele e self-explanatory. astfel, BST-ul ramane valid.
                BTNode<int>* minNode = node->right;
                ///mai intai il gasim
                while(minNode->left != NULL)
                    minNode = minNode->left;
                int rightMin = minNode->data;
                ///inlocuiesc cu nodul minim din dreapta gasit
                node->data = rightMin;
                ///apoi trebuie sters nodul acela, asa ca apelam recursia iar pentru subarborele dreapta.
                ///Il va gasi, acesta va fi frunza si il sterge, iar ca sa refacem legatura cu Node, atribui valoarea
                /// returnata de recursie lui node->right.
                node->right = deleteData(node->right, rightMin);
            }
        }
        return node;
    }

    BTNode<int>* insertData(BTNode<int> *node, int data){
        if(node == NULL){
            auto *n = new BTNode<int>(data);
            return n;
        }
        if(node->data > data){
            node->left = insertData(node->left, data);
        }
        else{
            node->right = insertData(node->right, data);
        }
        return node;
    }

    bool hasData(BTNode<int> *node, int data){
        if(node == NULL)
            return false;
        if(node->data == data)
            return true;
        if(node->data > data)
            return hasData(node->left, data);
        else
            return hasData(node->right, data);
    }

    void printTree(BTNode<int> *root){
        if(root==NULL)
            return;
        cout<<root->data<<": ";
        if(root->left)
            cout<<"L"<<root->left->data<<" ";
        if(root->right)
            cout<<"R"<<root->right->data<<" ";
        cout<<endl;
        printTree(root->left);
        printTree(root->right);
    }

    Pair convertToLinkedList(BTNode<int> *root){
        /// Primul cal: cand este frunza
        if(root==NULL){
            Pair p;
            p.head = NULL;
            p.tail = NULL;
            return p;
        }
        if(root->left == NULL && root->right == NULL){
            Pair p;
            p.head = root;
            p.tail = root;
            return p;
        }
        else if(root->left!=NULL && root->right==NULL){
            Pair leftLL = convertToLinkedList(root->left);
            leftLL.tail->right = root;
            ///asta pentru perechea finala, finalhead and finalTail
            Pair p;
            p.head = leftLL.head;
            p.tail = root;
            return p;
        }
        else if(root->left==NULL && root->right!=NULL){
            Pair rightLL = convertToLinkedList(root->right);
            root->right=rightLL.head;
            Pair p;
            p.head = root;
            p.tail = rightLL.tail;
            return p;
        }else{
            Pair leftLL = convertToLinkedList(root->left);
            Pair rightLL = convertToLinkedList(root->right);
            leftLL.tail->right=root;
            root->right = rightLL.head;

            Pair p;
            p.head = leftLL.head;
            p.tail = rightLL.tail;
            return p;
        }

    }

public:
    BST(){
        root = NULL;
    }
    ~BST(){
        delete root;
    }

    void deleteData(int data){
        root = deleteData(root, data);
    }

    void insertData(int data){
        root = insertData(root, data);
    }

    bool hasData(int data){
        return hasData(root, data);
    }

    void print(){
        printTree(root);
    }

    BTNode<int>* convertToLinkedList(){
        Pair p = convertToLinkedList(root);
        BTNode<int>* temp = p.head;
        while(temp){
            cout<<temp->data<<" ";
            temp->left =NULL;
            temp = temp->right;
        }
        return p.head;
    }
};


///aici sunt functii care lucreaza direct cu BTNode-urile. In main() testez si clasa BST
BTNode<int>* inputLevelWise(){
    int rootData;
    cout << "Enter root value:";
    cin >> rootData;
    ///creez radacina
    auto *root = new BTNode<int>(rootData);
    ///creez Queue-ul
    queue<BTNode<int> *> q;
    ///pun radacina in Queue
    q.push(root);
    while(!q.empty()) {
        auto *front = q.front();
        q.pop();
        /// dau valoarea copilului din stanga, 1.creez nodul, 2.il bag in Queue, apoi 3.il conectez la parinte
        cout << "Copilul stanga al nodului " << front->data << endl;
        int leftChildData;
        cin>>leftChildData;
        if(leftChildData!=-1) {
            ///1.
            auto *leftChild = new BTNode<int>(leftChildData);
            ///2.
            q.push(leftChild);
            ///3.
            front->left = leftChild;
        }
        /// dau valoarea copilului din dreapta, 1.creez nodul, 2.il bag in Queue, apoi 3.il conectez la parinte
        cout << "Copilul dreapta al nodului " << front->data << endl;
        int rightChildData;
        cin>>rightChildData;
        if(rightChildData!=-1) {
            ///1.
            auto *rightChild = new BTNode<int>(rightChildData);
            ///2.
            q.push(rightChild);
            ///3.
            front->right = rightChild;
        }
    }
    return root;
}

void printLevelWise(BTNode<int> *root){
    queue<BTNode<int>*> q;
    q.push(root);
    while(!q.empty()){
        auto *front=q.front();
        q.pop();
        cout<<front->data<<": ";
        if(front->left){
            cout<<"L"<<front->left->data;
            q.push(front->left);
        }
        if(front->right){
            cout<<" R"<<front->right->data;
            q.push(front->right);
        }
        cout<<endl;
    }
}

BTNode<int>* searchBST(BTNode<int> *root, int val){
    ///varianta resursiva
    /*if(root==NULL)
        return NULL;
    if(root->data==val)
        return root;
    if(val>root->data)
        return searchBST(root->right, val);
    else
        if(val<root->data)
            return searchBST(root->left, val);
    return NULL;
     */
    ///varianta iterativa
    while(root){
        if(root->data==val)
            return root;
        else
            if(val > root->data)
                root=root->right;
            else
                root=root->left;
    }
    return NULL;
}

int minValue(BTNode<int> *root){
    if(root==NULL)
        return -1;
    while(root->left!=NULL)
        root=root->left;
    return root->data;
}

int maxValue(BTNode<int> *root){
    if(root==NULL)
        return -1;
    while(root->right!=NULL)
        root=root->right;
    return root->data;
}

void rangeSum(BTNode<int> *root, int leftLimit, int rightLimit, int &sum){
    if(root==NULL)
        return;
    if(root->data>=leftLimit && root->data<=rightLimit)
        sum+=root->data;
    rangeSum(root->left, leftLimit, rightLimit, sum);
    rangeSum(root->right, leftLimit, rightLimit, sum);

}

void inorderTraversal(BTNode<int> *root){
    if (root == NULL)
        return;
    inorderTraversal(root->left);
    cout<<root->data<<" ";
    inorderTraversal(root->right);
}

void inorderTraversalCreateVector(BTNode<int> *root, vector<int> &v){
    if (root == NULL)
        return;
    inorderTraversalCreateVector(root->left, v);
    v.push_back(root->data);
    inorderTraversalCreateVector(root->right, v);
}

bool validBinaryTree(BTNode<int> *root){
    ///modul 1: inorder traversal este sortat
    vector<int> v;
    inorderTraversalCreateVector(root, v);
    for(int i=1;i<v.size();i++)
        if(v[i]<v[i-1])
            return false;
    return true;
}

/// metoda 2 pentru validBinaryTree
/// cu functia helperFunction doar verificam daca fiecare nod din BST respecta constraint-ul lui,
/// adica sa fie mai mic decat nodul parinte daca este in stanga sau mai mare daca e in dreapta
/// time complexity O(n), space complexity O(n) de la call stack-ul recursion-ului, altfel am putea spune ca e O(1)
bool helperFunction(BTNode<int> *root, long long minV = -10000000000, long long maxV = 10000000000){
    if(root == NULL)
        return true;
    // left values < root values
    bool left = helperFunction(root->left, minV, root->data);
    // root values < right values
    bool right = helperFunction(root->right, root->data, maxV);

    if(left && right && root->data>minV && root->data<maxV)
        return true;
    else
        return false;
}

bool isValidBST(BTNode<int> *root){
    return helperFunction(root);
}

BTNode<int>* sortedArrayToBSTHelper(vector<int> v, int s, int e){
    //for empty array
    if(s > e)
        return NULL;

    //now find middle element
    int mid = (s+e)/2;
    int rootData = v[mid];
    auto *root = new BTNode<int>(rootData);
    root->left = sortedArrayToBSTHelper(v, s, mid-1);
    root->right = sortedArrayToBSTHelper(v, mid + 1, e);
    return root;
}

BTNode<int>* sortedArrayToBST(vector<int> &v){
    int n = v.size();
    return sortedArrayToBSTHelper(v, 0, n-1);
}

int main(){
    /*
    /// input un BT pe nivele.
    BTNode<int> *root=inputLevelWise();

    cout<<"Print level wise:"<<endl;
    printLevelWise(root);
    cout<<endl;

    BTNode<int> *nodulCautat=searchBST(root,5);
    if(nodulCautat){
        cout<<"Nodul cautat exista: "<<nodulCautat->data<<endl;
    }
    else{
        cout<<"Nodul cautat nu exista"<<endl;
    }
    cout<<"min val: "<<minValue(root)<<endl;
    cout<<"max val: "<<maxValue(root)<<endl;

    cout<<endl;
    int suma=0;
    rangeSum(root, 6, 10, suma);
    cout<<"suma numerelor intre 6 si 10 din arbore este: "<<suma<<endl;
    cout<<endl;

    if(validBinaryTree(root)){
        cout<<"Arborele root este valid."<<endl;
    }
    else{
        cout<<"Arborele nu este valid."<<endl;
    }

    cout<<"Inorder Traversal: ";
    inorderTraversal(root);cout<<endl;

    //validBST metoda 2
    if(isValidBST(root)){
        cout<<"Arborele este valid.(metoda 2)"<<endl;
    }
    else{
        cout<<"Arborele nu este valid.(metoda 2)"<<endl;
    }

    ///test sorted Array to BST
    vector<int> inorder = {1, 2, 3, 4, 5, 6, 7, 8};
    BTNode<int> *rootFromSortedArray = sortedArrayToBST(inorder);
    printLevelWise(rootFromSortedArray);
    cout<<endl;
    */
    ///------------------------------------------------------------------------

    BST b;
    b.insertData(4);
    b.insertData(2);
    b.insertData(1);
    b.insertData(3);
    b.insertData(6);
    b.insertData(5);
    b.insertData(7);
    b.print();
    cout<<endl;
    //int data;
    //cout<<"Ce numar vreti sa verificati? "<<endl;
    //cin>>data;
    //cout<<b.hasData(10);


    b.deleteData(100);
    b.print();
    cout<<endl;

    BTNode<int>* head= b.convertToLinkedList();


}