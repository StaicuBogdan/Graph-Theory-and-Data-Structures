#include <iostream>
#include <vector>
#include <queue>

using namespace std;

template<typename T>
class TreeNode {
public:
    T data;
    vector<TreeNode<T> *> children;

    TreeNode(T data) {
        this->data = data;
    }

    ~TreeNode(){
        for(int i=0;i<=children.size();i++)
            delete children[i];
    }
};

void printRecursive(TreeNode<int> *root) {
    if (root == NULL)
        return;
    cout << root->data << " : ";
    for (auto &i : root->children)
        cout << i->data << ", ";
    cout << endl;
    for (int i = 0; i < root->children.size(); i++)
        printRecursive(root->children[i]);
}

TreeNode<int> *inputRecursive() {
    int rootData;
    cout << "Enter root value:";
    cin >> rootData;
    auto *root = new TreeNode<int>(rootData);
    int n;
    cout << "Enter the nr. of chidlren of " << rootData << ": ";
    cin >> n;
    cout << endl;
    for (int i = 0; i <= n - 1; i++) {
        auto *child = inputRecursive();
        root->children.push_back(child);
    }
    return root;
}
///am incercat sa implementez altfel cu doua functii dar nu a mers, iar apoi am implementat cu Queue
/*
void inputChildren(TreeNode<int> *root, int n){
    for(int i=0;i<=n-1;i++){
        int dataChild;
        cout<<"Enter data for child "<<i<<": ";cin>>dataChild;
        auto *child= new TreeNode<int>(dataChild);
        root->children.push_back(child);
    }
}

TreeNode<int>* inputLevelWise(){
    int rootData;
    cout<<"Enter root value:";cin>>rootData;
    auto *root=new TreeNode<int>(rootData);
    int n;
    cout<<"Enter the nr. of chidlren of "<<rootData<<": ";cin>>n;
    cout<<endl;
    inputChildren(root,n);
}
*/

///implementare inputLevelWise folosind Queue
TreeNode<int> *inputLevelWise() {
    int rootData;
    cout << "Enter root value:";
    cin >> rootData;
    auto *root = new TreeNode<int>(rootData);
    queue<TreeNode<int> *> q;
    q.push(root);
    /// in Queue pun radacina, o salvez in nodul *front
    while (!q.empty()) {
        auto *front = q.front();
        q.pop();
        ///am scos radacina din Queue, apoi cer numarul de copii ai radacinii
        cout << "Enter the nr. of chidlren of " << front->data << endl;
        int n;
        cin >> n;
        /// aplic cei 3 pasi pentru fiecare din cei n copii, si ma opresc cand se goleste Queue-ul
        for (int i = 1; i <= n; i++) {
            int childData;
            cout << "Dati valoarea copilului nr. " << i << " al nodului " << front->data << endl;
            cin >> childData;
            /// 1. create node
            auto *child = new TreeNode<int>(childData);
            /// 2. push node
            q.push(child);
            /// 3.connect to parent vector
            front->children.push_back(child);
        }
    }
    return root;
}

///functia de printare pe nivele, asemanator cu ce de mai sus, cu mici modificari, caci avem deja nodurile
void printLevelWise(TreeNode<int> *root) {
    queue<TreeNode<int> *> q;
    q.push(root);
    while (!q.empty()) {
        auto *front = q.front();
        q.pop();
        cout << front->data << ": ";
        for (int i = 0; i < front->children.size(); i++) {
            cout << front->children[i]->data << " ";
            q.push(front->children[i]);
        }
        cout << endl;
    }
};

int countNodes(TreeNode<int> *root) {
    if (root == NULL)
        return 0;
    ///s este 1 pentru fiecare nod, acesta fiind el insusi, iar pentru fiecare nod aduna la suma fiii si fiii fiilor si tot asa...
    int s = 1;
    for (int i = 0; i < root->children.size(); i++) {
        s += countNodes(root->children[i]);
    }
    return s;
}

int height(TreeNode<int> *root) {
    if (root == NULL)
        return 0;
    ///pentru fiecare sub-arbore avem maxHeight egal cu zero la inceput, pana functia recursiva ajunge jos de tot pe ultimul nivel
    ///iar pentru fiecare nivel, returneaza maxHeight+1 cand "urca" inapoi spre radacina, ajungand sa calculeze inaltimea
    ///maxima pentru fiecare ramura a arborelui
    int maxHeight = 0;
    for (auto &i : root->children) {
        //int childHeight = height(i);
        //if (childHeight > maxh)
            //maxh = childHeight;
        maxHeight=max(maxHeight, height(i));
    }
    return maxHeight + 1;
}

void printNodesAtLevelK(TreeNode<int> *root, int k){
    if(root==NULL)
        return;
    ///scadem k cu cate 1 pana cand ajunge la zero, deci am facut k pasi de la radacina, deci afisam nodul
    if(k==0){
        cout<<root->data<<" ";
        return;
    }
    ///apelam functia recursiv cu k-1 pana ajunge k == 0
    for(int i=0;i<root->children.size();i++){
        printNodesAtLevelK(root->children[i], k-1);
    }
}

void printNodesAtLevelK2(TreeNode<int> *root, int k, int currentDepth){
    if(root==NULL)
        return;
    ///scadem k cu cate 1 pana cand ajunge la zero, deci am facut k pasi de la radacina, deci afisam nodul
    if(k==currentDepth){
        cout<<root->data<<" ";
        return;
    }
    ///apelam functia recursiv cu k-1 pana ajunge k == 0
    for(int i=0;i<root->children.size();i++){
        printNodesAtLevelK2(root->children[i], k, currentDepth+1);
    }
}


int countLeafNodes(TreeNode<int> *root){
    if(root==NULL)
        return 0;
    int leaf=0;
    if(root->children.empty())
        leaf=1;
    for(int i=0;i<root->children.size();i++){
        leaf=leaf+countLeafNodes(root->children[i]);
    }
    return leaf;
}

void countLeafNodes2(TreeNode<int> *root, int &leaves){
    if(root==NULL)
        return;
    if(root->children.empty()) {
        leaves++;
        return;
    }
    for(auto & i : root->children)
        countLeafNodes2(i,leaves);
}

void preOrderTraversal(TreeNode<int> *root) {
    if (root == NULL)
        return;
    cout << root->data<< " ";
    for (int i = 0; i < root->children.size(); i++)
        preOrderTraversal(root->children[i]);
}

void postOrderTraversal(TreeNode<int> *root){
    if (root == NULL)
        return;
    for (int i = 0; i < root->children.size(); i++)
        postOrderTraversal(root->children[i]);
    cout << root->data<< " ";
}

void deleteTree(TreeNode<int> *root){
    if (root == NULL)
        return;
    for (auto & i : root->children)
        deleteTree(i);
    delete root;
}

int main() {
    /*auto *n1=new TreeNode<int>(2);
    auto *n2=new TreeNode<int>(3);
    auto *n3=new TreeNode<int>(4);
    root->children.push_back(n1);
    root->children.push_back(n2);
    root->children.push_back(n3);
    */

    //auto *root=inputRecursive();

    auto *root = inputLevelWise();
    cout<<"Print Level wise: "<<endl;
    printLevelWise(root);
    cout<<"Nr of nodes: " << countNodes(root)<<endl;
    cout<<"Height: " << height(root)<<endl;
    cout<<"Nodes at depth 2: ";
    printNodesAtLevelK(root,2);
    cout<<endl;
    cout<<"Leaf nodes: "<<countLeafNodes(root)<<endl;

    int l1=0;
    countLeafNodes2(root, l1);
    cout<<"Leaf nodes mode 2: "<<l1<<endl;

    cout<<"Preorder Traversal: ";
    preOrderTraversal(root);
    cout<<endl;

    cout<<"Postorder Traversal: ";
    postOrderTraversal(root);
    cout<<endl;

    //deleteTree(root);
    delete root;
}
