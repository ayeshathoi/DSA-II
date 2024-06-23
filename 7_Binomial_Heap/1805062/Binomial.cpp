#include<bits/stdc++.h>
using namespace std;

struct Node
{
    int data, degree;
    Node *child, *sibling, *parent;
};

list<Node*> priorityQueue;

Node* newNode(int key)
{
    Node *temp = new Node;
    temp->data = key;
    temp->degree = 0;
    temp->child = temp->parent = temp->sibling = NULL;
    return temp;
}


void setData(Node *s,int key)
{
    s->data=key;
}

int getData(Node *s)
{
    return s->data;
}
int getDegree(Node *s)
{
    return s->degree;
}

Node* getParent(Node *s)
{
    return s->parent;
}

Node* Merge(Node *firstBino, Node *secondBino)
{
    if (secondBino->data > firstBino->data)
        swap(firstBino, secondBino);

    secondBino->parent = firstBino;
    secondBino->sibling = firstBino->child;
    firstBino->child = secondBino;
    firstBino->degree++;

    return firstBino;
}

list<Node*> Union(list<Node*> firstList,list<Node*> secondList)
{
    list<Node*> thirdList;
    list<Node*>::iterator firstIterator = firstList.begin();
    list<Node*>::iterator secondIterator = secondList.begin();
    while (firstIterator!=firstList.end() && secondIterator!=secondList.end())
    {
        if((*firstIterator)->degree <= (*secondIterator)->degree)
        {
            thirdList.push_back(*firstIterator);
            firstIterator++;
        }

        else
        {
            thirdList.push_back(*secondIterator);
            secondIterator++;
        }
    }

    while (firstIterator != firstList.end())
    {
        thirdList.push_back(*firstIterator);
        firstIterator++;
    }


    while (secondIterator!=secondList.end())
    {
        thirdList.push_back(*secondIterator);
        secondIterator++;
    }
    return thirdList;
}

list<Node*> Resize(list<Node*> priorityQueue)
{
    if (priorityQueue.size() <= 1)
        return priorityQueue;
    list<Node*> newPriorityQueue;
    list<Node*>::iterator iterator1,iterator2,iterator3;
    iterator1 = iterator2 = iterator3 = priorityQueue.begin();

    if (priorityQueue.size() == 2)
    {
        iterator2 = iterator1;
        iterator2++;
        iterator3 = priorityQueue.end();
    }
    else
    {
        iterator2++;
        iterator3=iterator2;
        iterator3++;
    }
    while (iterator1 != priorityQueue.end())
    {
        if (iterator2 == priorityQueue.end())
            iterator1++;
        else if ((*iterator1)->degree < (*iterator2)->degree)
        {
            iterator1++;
            iterator2++;
            if(iterator3!=priorityQueue.end())
                iterator3++;
        }

        else if (iterator3!=priorityQueue.end() &&
                 (*iterator1)->degree == (*iterator2)->degree &&
                 (*iterator1)->degree == (*iterator3)->degree)
        {
            iterator1++;
            iterator2++;
            iterator3++;
        }

        else if ((*iterator1)->degree == (*iterator2)->degree)
        {
            Node *temp;
            *iterator1 = Merge(*iterator1,*iterator2);
            iterator2 = priorityQueue.erase(iterator2);
            if(iterator3 != priorityQueue.end())
                iterator3++;
        }
    }
    return priorityQueue;
}

list<Node*> insertTree(Node *tree)
{
    list<Node*> auxNode;

    auxNode.push_back(tree);

    auxNode = Union(priorityQueue,auxNode);

    return Resize(auxNode);
}


list<Node*> removeMax(Node *tree)
{
    list<Node*> heap;
    Node *temp = tree->child;
    Node *lo;

    while (temp)
    {
        temp -> parent = NULL;
        lo = temp;
        temp = temp->sibling;
        lo->sibling = NULL;
        heap.push_front(lo);
    }
    return heap;
}

list<Node*> Insert(int key)
{
    Node *temp = newNode(key);
    return insertTree(temp);
}

Node* FindMax()
{
    list<Node*>::iterator it = priorityQueue.begin();
    Node *temp = *it;
    while (it != priorityQueue.end())
    {
        if ((*it)->data > temp->data)
            temp = *it;
        it++;
    }
    return temp;
}

list<Node*> extractMax()
{
    list<Node*> newPriorityQueue,lo;
    Node *temp;

    temp = FindMax();
    Node *BinomialtreeNum=temp;
    list<Node*>::iterator it = priorityQueue.begin();;
    while (it != priorityQueue.end())
    {
        if (*it != temp)
        {

            newPriorityQueue.push_back(*it);
        }
        it++;
    }

    cout<<"ExtractMax returned "<<temp->data<<endl;

    lo = removeMax(temp);

    newPriorityQueue = Union(newPriorityQueue,lo);
    newPriorityQueue = Resize(newPriorityQueue);

    return newPriorityQueue;
}

int levelnum(Node *h)
{
    int c = 0;
    Node *presentNode = getParent(h);
    while(presentNode!=NULL)
    {
        c++;
        presentNode = getParent(presentNode);
    }
    return c;
}

void printTree(Node *presentNode, vector<list<int>> &levelOrder)
{
    while (presentNode)
    {
        levelOrder[levelnum(presentNode)].push_back(presentNode->data);
        printTree(presentNode->child, levelOrder);
        presentNode = presentNode->sibling;
    }
}

Node* presentNode(Node *present,int key)
{
    while (present)
    {

        Node *auxNode=presentNode(present->child,key);
        if(auxNode!=NULL)
            return auxNode;
        if(present->data==key)
            return present;
        present = present->sibling;
    }
    return NULL;

}


void printHeap()
{
    int arr[100];
    double c=0;
    int i=0;
    list<Node*> ::iterator it;
    it = priorityQueue.begin();
    while (it != priorityQueue.end())
    {
        arr[i]=getDegree(*it);
        cout<<"Binomial Tree B"<<arr[i]<<endl;
        vector<list<int>> levelOrder(arr[i] + 1);
        printTree(*it, levelOrder);

        for(int j = 0; j <= arr[i]; j++)
        {
            cout << "Level " << j << ":";
            for(int x : levelOrder[j])cout << " " << x;
            cout << endl;
        }
        it++;
        i++;
    }
}

Node* Search(int key)
{
    list<Node*> ::iterator it;
    it = priorityQueue.begin();
    while (it != priorityQueue.end())
    {
        Node *temp = presentNode(*it,key);
        if(temp)
            return temp;
        it++;
    }
}

void Increasekey(int prev,int newk)
{
    if(prev>=newk)
        return;
    Node *mp = Search(prev);
    if(mp==NULL) return;
    setData(mp,newk);
    Node *presentNode = getParent(mp);
    while(getParent(mp)!=NULL  && getData(presentNode) < getData(mp))
    {
        int num = getData(presentNode);
        int val = getData(mp);
        setData(mp,num);
        setData(presentNode,val);
        mp = presentNode;
        presentNode = getParent(presentNode);
    }
}


int main()
{
    ifstream in("offline.txt");

    while (in)
    {
        string s;
        in>>s;
        if(in.eof())
            break;
        int n,n2;
        if(s[2]=='S')
        {
            in>>n;
            priorityQueue = Insert(n);
            cout<<"Inserted "<<n<<endl;
        }
        if(s[2]=='I')
        {
            cout<<"Printing Binomial Heap...\n";
            cout<<"-------------------------"<<endl;
            printHeap();
            cout<<"-------------------------"<<endl;
        }
        if(s[2]=='C')
        {
            in>>n>>n2;
            Increasekey(n,n2);
            cout<<"Increased "<<n<<" . The updated value is "<<n2<<" ."<<endl;
        }
        if(s[2]=='T')
        {
            priorityQueue=extractMax();

        }
        if(s[2]=='N')
        {
            Node *temp=FindMax();
            cout<<"FindMax returned "<<temp->data<<endl;
        }

    }
    in.close();
    return 0;
}
