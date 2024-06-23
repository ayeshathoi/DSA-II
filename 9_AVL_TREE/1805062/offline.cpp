#include<bits/stdc++.h>
using namespace std;

class Node
{
public:
    int key;
    Node *left;
    Node *right;
    int height;

};

Node* newNode(int key)
{
    Node* node = new Node();
    node->key = key;
    node->left = NULL;
    node->right = NULL;
    node->height = 1;
    return(node);
}

int maximum(int a, int b)
{
    return (a > b)? a : b;
}

int height(Node *N)
{
    if (N == NULL)
        return 0;
    return N->height;
}

Node *RightRotate(Node *y)
{
    Node *x = y->left;
    Node *T2 = x->right;

    x->right = y;
    y->left = T2;


    y->height = maximum(height(y->left),
                        height(y->right)) + 1;
    x->height = maximum(height(x->left),
                        height(x->right)) + 1;


    return x;
}

Node *LeftRotate(Node *x)
{
    Node *y = x->right;
    Node *T2 = y->left;


    y->left = x;
    x->right = T2;

    x->height = maximum(height(x->left),
                        height(x->right)) + 1;
    y->height = maximum(height(y->left),
                        height(y->right)) + 1;

    return y;
}

int getBalance(Node *N)
{
    if (N == NULL)
        return 0;
    return height(N->left) - height(N->right);
}

Node * minValueNode(Node* node)
{
    Node* current = node;

    while (current->left != NULL)
        current = current->left;

    return current;
}


Node* Deletion(Node* node, int key)
{
  if (node == NULL)
        return NULL;

    if ( key < node->key )
        node->left = Deletion(node->left, key);


    else if( key > node->key )
        node->right = Deletion(node->right, key);


    else
    {
        if( (node->left == NULL) ||
                (node->right == NULL) )
        {
            Node *temp = node->left ?node->left :node->right;

			delete node;
            node = temp;
        }

          else
        {
            Node* temp = minValueNode(node->right);
            node->key = temp->key;
            node->right = Deletion(node->right,
                                     temp->key);

        }
    }


    if (node == NULL)
        return node;

    node->height = 1 + maximum(height(node->left),
                               height(node->right));

    int BalanceCalculation = getBalance(node);
     if(BalanceCalculation<-1||BalanceCalculation>1)
        cout<<"Height invariant violated.\nAfter rebalancing: ";

    if (BalanceCalculation > 1 &&
            getBalance(node->left) >= 0)
        return RightRotate(node);


    if (BalanceCalculation > 1 &&
            getBalance(node->left) < 0)
    {
        node->left = LeftRotate(node->left);
        return RightRotate(node);
    }


    if (BalanceCalculation < -1 &&
            getBalance(node->right) <= 0)
        return LeftRotate(node);

    if (BalanceCalculation < -1 &&
            getBalance(node->right) > 0)
    {
        node->right = RightRotate(node->right);
        return LeftRotate(node);
    }

    return node;
}


Node* Insertion(Node* node, int key)
{
    if (node == NULL)
        return(newNode(key));

    if (key < node->key)
        node->left = Insertion(node->left, key);
    else if (key > node->key)
        node->right = Insertion(node->right, key);
    else
        return node;

    node->height = 1 + maximum(height(node->left),height(node->right));

    int BalanceCalculation = getBalance(node);

    if(BalanceCalculation<-1||BalanceCalculation>1)
        cout<<"Height invariant violated.\nAfter rebalancing: ";

    if (BalanceCalculation > 1 && key < node->left->key)
        return RightRotate(node);
    if (BalanceCalculation < -1 && key > node->right->key)
        return LeftRotate(node);

    if (BalanceCalculation > 1 && key > node->left->key)
    {
        node->left = LeftRotate(node->left);
        return RightRotate(node);
    }


    if (BalanceCalculation < -1 && key < node->right->key)
    {
        node->right = RightRotate(node->right);
        return LeftRotate(node);
    }

    return node;
}


bool Search(Node* root, int key)
{

    if (root == NULL)
        return false;

    else if (root->key == key)
        return true;

    else if (root->key > key)
    {
        bool val = Search(root->left, key);
        return val;
    }
    else
    {
        bool val = Search(root->right, key);
        return val;
    }
}


void print(Node *root)
{
    if(root!=NULL)
    {
        cout<<root->key;
        if(root->left==NULL && root->right==NULL)
            return;
        if(root->left!=NULL)
            cout << "(", print(root->left), cout << ")";
        if(root->left==NULL)
            cout<<"()";
        if(root->right!=NULL)
            cout << "(", print(root->right), cout << ")";
        if(root->right==NULL)
            cout<<"()";
    }
}

int main()
{
    ifstream in("input.txt");
    Node *root = NULL;
    while (in)
    {

        string s;
        in>>s;
        if(in.eof())
            break;
        int n;

        if(s[0]=='I')
        {
            in>>n;
            root = Insertion(root, n);
            print(root);
            cout<<"\n";
        }
        if(s[0]=='F')
        {
            in>>n;
            bool i = Search(root,n);
            if(i)
                cout<<"True";
            else cout<<"False";
             cout<<"\n";
        }

        if(s[0]=='D')
        {
            in>>n;
            root = Deletion(root,n);
            print(root);
            cout<<"\n";
        }

    }
    in.close();
    return 0;

}
