#include <iostream>
#include <queue>
#include <vector>

using namespace std;

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

void printRecursive(BTNode<int> *root){
    if(root==NULL)
        return;
    cout<<root->data<<": ";
    if(root->left)
        cout<<"L"<<root->left->data<<" ";
    if(root->right)
        cout<<"R"<<root->right->data<<" ";
    cout<<endl;
    printRecursive(root->left);
    printRecursive(root->right);
}

BTNode<int>* inputRecursive(){
    int rootData;
    cout << "Enter root value:";
    cin >> rootData;
    if(rootData==-1)
        return NULL;
    auto *root = new BTNode<int>(rootData);
    root->left=inputRecursive();
    root->right=inputRecursive();
    return root;
}

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
///folosesc NULL pentru a marca sfarsitul unui nivel al arborelui
void levelTraversal(BTNode<int> *root){
    queue<BTNode<int>*> q;
    ///adaug radacina in coada si apoi NULL, caci e singura pe nivel
    q.push(root);
    q.push(NULL);
    while(!q.empty()){
        auto *front=q.front();
        q.pop();
        ///daca primul element al cozii este NULL, inseamna ca am parcurs toate nodurile de pe acel nivel si am adaugat toti
        ///copiii in coada, deci mai trebuie sa adaugam un NULL. Daca nu mai avem copii adaugati, nu adaugam nici NULL
        if(front==NULL) {
            cout << endl;
            if(!q.empty())
                q.push(NULL);
        }
        else {
            cout<<front->data<<" ";
            if (front->left) {
                q.push(front->left);
            }
            if (front->right) {
                q.push(front->right);
            }
        }
    }
}

int countNodes(BTNode<int> *root) {
    if (root == NULL)
        return 0;
    ///s este 1 pentru fiecare nod, acesta fiind el insusi, iar pentru fiecare nod aduna la suma fiii si fiii fiilor si tot asa...
    return countNodes(root->left)+countNodes(root->right)+1;
}

void inorderTraversal(BTNode<int> *root){
    if (root == NULL)
        return;
    inorderTraversal(root->left);
    cout<<root->data<<" ";
    inorderTraversal(root->right);
}

void preorderTraversal(BTNode<int> *root){
    if (root == NULL)
        return;
    cout<<root->data<<" ";
    preorderTraversal(root->left);
    preorderTraversal(root->right);
}

void postorderTraversal(BTNode<int> *root){
    if (root == NULL)
        return;
    postorderTraversal(root->left);
    postorderTraversal(root->right);
    cout<<root->data<<" ";
}

int height(BTNode<int> *root){
    if(root==NULL)
        return 0;
    int maxheight=0;
    maxheight=max(maxheight,height(root->left));
    maxheight=max(maxheight,height(root->right));
    return maxheight+1;

}

bool compare(BTNode<int> *leftTree, BTNode<int> *rightTree){
    ///daca une din radacini nu exista, e false
    if(leftTree==NULL && rightTree!=NULL)
        return false;
    if(leftTree!=NULL && rightTree==NULL)
        return false;
    ///daca ambele sunt NULL, inseamna ca s-a terminat arborele
    if(leftTree==NULL && rightTree==NULL)
        return true;
    ///daca au valori diferite radacinile simetrice, e false iar
    if(leftTree->data!=rightTree->data)
        return false;
    ///mergem mai jos in arbore si comparam partea dreapta a arborelui din stanga cu partea stanga a celui din dreapta
    //
    //         1
    //      /  |  \
    //     2<--|-->2
    //    / \  |  / \
    //   3  4  |  4  3
    //
    ///de exemplu suntem cu leftTree si rightTree la 2, trebuie sa comparam pe 4 din stanga de mai jos cu 4 din dreapta
    /// adica dreapta lui leftTree cu stanga lui rightTree

    ///returnam true doar daca sunt timetrici ambii subarbori leftTree si rightTree
    return compare(leftTree->right,rightTree->left) && compare(leftTree->left, rightTree->right);

}

bool symmetric(BTNode<int> *root){
    ///daca radacina este NULL, e simetric
    if(root==NULL)
        return true;
    ///apoi comparam arborele din stanga cu cel din dreapta
    return compare(root->left, root->right);
}

bool searchNode(BTNode<int> *root, int k){
    if(root==NULL)
        return false;
    if(root->data==k)
        return true;
    return (searchNode(root->left,k) || searchNode(root->right,k));
}

int minValue(BTNode<int> *root){
    if(root==NULL)
        return INT_MAX;
    int leftMinim=minValue(root->left);
    int rightMinim=minValue(root->right);
    return min(root->data, min(rightMinim, leftMinim));
}

void minValue2(BTNode<int> *root, int &answer){
    if(root==NULL)
        return;
    if(root->data<answer)
        answer=root->data;
    minValue2(root->left, answer);
    minValue2(root->right, answer);
}

int maxValue(BTNode<int> *root){
    if(root==NULL)
        return INT_MIN;
    int leftMaxim=maxValue(root->left);
    int rightMaxim=maxValue(root->right);
    return max(root->data, max(rightMaxim, leftMaxim));
}

void maxValue2(BTNode<int> *root, int &answer){
    if(root==NULL)
        return;
    if(root->data>answer)
        answer=root->data;
    maxValue2(root->left, answer);
    maxValue2(root->right, answer);
}

int countLeafNodes(BTNode<int> *root){
    if(root==NULL)
        return 0;
    int leaf=0;
    if(root->left==NULL && root->right==NULL)
        return 1;
    leaf=leaf + countLeafNodes(root->right) + countLeafNodes(root->left);
    return leaf;
}

void countLeafNodes2(BTNode<int> *root, int &leaves){
    if(root==NULL)
        return;
    if(root->left==NULL && root->right==NULL){
        leaves++;
        return;
    }
    countLeafNodes2(root->right, leaves);
    countLeafNodes2(root->left, leaves);
}

BTNode<int>* buildTree(int Inorder[], int InorderStart, int InroderEnd, int Preorder[], int PreorderStart, int PreorderEnd){
    if(InorderStart>InroderEnd)
        return NULL;
    ///valoarea radacinii va fi primul numar din vectorul preorder
    int rootData=Preorder[PreorderStart];
    auto *treeRoot=new BTNode<int>(rootData);

//    int lInS=InorderStart,lInE, lPreS=PreorderStart+1, lPreE;
//    int rInS, rInE, rPreS, rPreE;
//    for(int i=InorderStart;i<=InroderEnd;i++)
//        if(Inorder[i]==treeRoot->data){
//            lInE=i-1;
//            lPreE=PreorderStart+i;
//            rInS=i+1;
//            rInE=InroderEnd;
//            rPreS=PreorderStart+i+1;
//            rPreE=PreorderEnd;
//            break;
//        }

    int rootIndex=-1;
    for(int i=InorderStart;i<=InroderEnd;i++){
        if(Inorder[i]==rootData){
            rootIndex=i;
            break;
        }
    }

    int leftInS= InorderStart;
    int leftInE=rootIndex-1;
    int leftPreS=PreorderStart+1;
    int leftPreE=leftPreS+leftInE-leftInS;

    int rightInS=rootIndex+1;
    int rightInE=InroderEnd;
    int rightPreS=leftPreE+1;
    int rightPreE=PreorderEnd;

    treeRoot->left=buildTree(Inorder, leftInS, leftInE, Preorder, leftPreS, leftPreE);
    treeRoot->right=buildTree(Inorder, rightInS, rightInE, Preorder, rightPreS, rightPreE);
    return treeRoot;
}

BTNode<int>* buildTreeFromPostorder(int Inorder[], int InorderStart, int InroderEnd, int Postorder[], int PostorderStart, int PostorderEnd) {
    if (InorderStart > InroderEnd)
        return NULL;
    ///valoarea radacinii va fi primul numar din vectorul preorder
    int rootData = Postorder[PostorderEnd];
    auto *treeRoot = new BTNode<int>(rootData);

    int rootIndex = -1;
    for (int i = InorderStart; i <= InroderEnd; i++) {
        if (Inorder[i] == rootData) {
            rootIndex = i;
            break;
        }
    }

    int leftInS = InorderStart;
    int leftInE = rootIndex-1;
    int leftPostS = PostorderStart;
    int leftPostE = leftPostS+leftInE-leftInS;

    int rightInS = rootIndex+1;
    int rightInE = InroderEnd;
    int rightPostS = leftPostE+1;
    int rightPostE = PostorderEnd-1;

    treeRoot->left = buildTreeFromPostorder(Inorder, leftInS, leftInE, Postorder, leftPostS, leftPostE);
    treeRoot->right = buildTreeFromPostorder(Inorder, rightInS, rightInE, Postorder, rightPostS, rightPostE);
    return treeRoot;
}

int diameterOfTree(BTNode<int> *root){
    if(root==NULL)
        return 0;

    ///avem 3 cazuri, primul unde diametrul este egal pur si simplu cu inaltimile celor doua jumatati adunate
    ///dar si cazurile in care subarborele drept e mult mai mare decat cel stang sau invers
    int option1= height(root->left)+height(root->right);
    int option2= diameterOfTree(root->left);
    int option3= diameterOfTree(root->right);

    return max(option1, max(option2,option3));
    ///complexitate NlogN daca e arbore mai balanced, N^2 daca e arbore cu o ramura mult mai mare decat cealalta
}

bool getPath(BTNode<int> *root, int nodeValue, vector<int> &v){
    if(root==NULL)
        return false;
    v.push_back(root->data);
    if(root->data==nodeValue)
        return true;

    bool left= getPath(root->left, nodeValue, v);
    bool right= getPath(root->right, nodeValue, v);

    if(left || right){
        return true;
    }
    else{
        v.pop_back();
        return false;
    }
}

int main() {
    /*
    BTNode<int> *root=new BTNode<int>(1);
    BTNode<int> *n1=new BTNode<int>(2);
    BTNode<int> *n2=new BTNode<int>(3);

    root->left=n1;
    root->right=n2;
    */

    //BTNode<int> *root=inputRecursive();

    BTNode<int> *root=inputLevelWise();
    cout<<"Print recursive:"<<endl;
    printRecursive(root);
    cout<<endl;
    cout<<"Print level wise:"<<endl;
    printLevelWise(root);
    cout<<endl;

    cout<<"Level traversal: "<<endl;
    levelTraversal(root);

    cout<<"Nr of nodes: "<<countNodes(root)<<endl;

    inorderTraversal(root);
    cout<<endl;
    preorderTraversal(root);
    cout<<endl;
    postorderTraversal(root);
    cout<<endl;

    cout<<"height :" <<height(root)<<endl;

    cout<<"Arbore simetric: "<<symmetric(root)<<endl;

    cout<<"Exista nodul cu valoarea 6 sau nu? "<<searchNode(root, 6)<<endl;

    cout<<"Valoarea minima din arbore: "<<minValue(root)<<endl;
    int answerMin=INT_MAX;
    cout<<"Valoarea minima din arbore V2: ";minValue2(root, answerMin);cout<<answerMin<<endl;

    cout<<"Valoarea maxima din arbore: "<<maxValue(root)<<endl;
    int answerMax=INT_MIN;
    cout<<"Valoarea maxima din arbore V2: ";maxValue2(root, answerMax);cout<<answerMax<<endl;

    cout<<"Nr de frunze: "<<countLeafNodes(root)<<endl;
    int leaves=0;
    cout<<"Nr de frunze2: ";countLeafNodes2(root, leaves);cout<<leaves<<endl;

    int preorder[8]={1,2,4,3,5,7,8,6};
    int inorder[8]={4,2,1,7,5,8,3,6};
    BTNode<int> *root2=buildTree(inorder,0,7,preorder,0,7);
    cout<<"Print Level Wise root2: "<<endl;
    printLevelWise(root2);cout<<endl;

    cout<<"Diametrul arborelui root: "<<diameterOfTree(root)<<endl;

    vector<int> v;
    if(getPath(root, 9, v))
        for(int i : v)
            cout<<i<<" ";
    else
        cout<<"Value not found";
    cout<<endl;

    delete root;
    delete root2;
}
