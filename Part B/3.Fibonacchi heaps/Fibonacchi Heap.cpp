#include<bits/stdc++.h>
using namespace std;

template <class T>
class FibonacciHeap{
    class Node{
    public:
        T value;
        Node *cHead, *cTail, *prv, *nxt, *par;
        bool marked;
        int deg;
        
        Node(T val = T()){
            value = val;
            cHead = cTail = prv = nxt = par = NULL;
            marked = false;
            deg = 0;
        }
        
        Node* merge(Node *nd, function<bool(T, T)> &func){
            if(func(nd -> value, value)){
                nd -> prv = prv;
                nd -> nxt = nxt;
                this -> par = nd;
                nd -> deg++;
                if(nd -> cHead){
                    nd -> cTail -> nxt = this;
                    prv = nd -> cTail;
                    nxt = NULL;
                }else{
                    nd -> cHead = this;
                    prv = nxt = NULL;
                }
                nd -> cTail = this;
                return nd;
            }
            deg++;
            nd -> par = this;
            if(cHead){
                cTail -> nxt = nd;
                nd -> prv = cTail;
                nd -> nxt = NULL;
            }else{
                cHead = nd;
                nd -> prv = nd -> nxt = NULL;
            }
            cTail = nd;
            return this;
        }
        
        void clear(){
            while(cHead){
                cHead -> clear();
                Node *t = cHead -> nxt;
                delete cHead;
                cHead = t;
            }
        }
    };
    
    Node *head, *tail, *mn;
    size_t sz;
    function<bool(T, T)> func;
    
    void adjust(){
        int K = 32 - __builtin_clz((int)sz);
        Node* temp[K];
        for(int i = 0; i < K; i++)temp[i] = NULL;
        Node* cur = head;
        mn = head;
        while(cur != NULL){
            if(temp[cur -> deg] != NULL){
                Node *t = temp[cur -> deg];
                
                if(t -> prv)t -> prv -> nxt = t -> nxt;
                else head = t -> nxt;
                if(t -> nxt)t -> nxt -> prv = t -> prv;
                else tail = t -> prv;
                
                temp[cur -> deg] = NULL;
                cur = cur -> merge(t, func);
            }else{
                if(func(cur -> value, mn -> value))mn = cur;
                temp[cur -> deg] = cur;
                cur = cur -> nxt;
            }
        }
    }
    
    void separate(Node *node){
        node -> marked = false;
        if(node -> par == NULL)return;
        if(node -> prv)node -> prv -> nxt = node -> nxt;
        else node -> par -> cHead = node -> nxt;
        if(node -> nxt)node -> nxt -> prv = node -> prv;
        else node -> par -> cTail = node -> prv;
        tail -> nxt = node;
        node -> prv = tail;
        node -> nxt = NULL;
        tail = node;
        if(node -> par -> marked)separate(node -> par);
        node -> par = NULL;
    }
    
    
    void merge(Node *h, Node *t){
        if(h == NULL)return;
        if(empty()){
            head = h;
            tail = t;
            return;
        }
        
        tail -> nxt = h;
        h -> prv = tail;
        tail = t;
    }
public:
    
    FibonacciHeap(function<bool(T, T)> f = less<T>()){
        head = tail = mn = NULL;
        sz = 0;
        func = f;
    }
    
    bool empty(){
        return sz == 0;
    }
    
    Node* push(T x){
        sz++;
        Node *nw = new Node(x);
        if(head == NULL){
            head = tail = mn = nw;
            return nw;
        }
        nw -> prv = tail;
        tail -> nxt = nw;
        tail = nw;
        if(func(nw -> value, mn -> value))
            mn = nw;
        return nw;
    }
    
    void merge(FibonacciHeap<T> &h){
        if(h.head == NULL)return;
        if(empty()){
            head = h.head;
            tail = h.tail;
            mn = h.mn;
            sz = h.sz;
            return;
        }
        
        tail -> nxt = h.head;
        (h.head) -> prv = tail;
        tail = h.tail;
        
        if(func((h.mn) -> value, mn -> value))
            mn = h.mn;
        sz += h.sz;
    }
    
    T pop(){
        if(empty())return T();
        Node *h =  mn -> cHead;
        Node *t = mn -> cTail;
        T v = mn -> value;
        for(auto x = h; x; x = x -> nxt)x -> par = NULL;
        merge(h, t);
        if(mn -> prv)mn -> prv -> nxt = mn -> nxt;
        else head = mn -> nxt;
        if(mn -> nxt)mn -> nxt -> prv = mn -> prv;
        else tail = mn -> prv;
        
        delete mn;
        sz--;
        
        if(empty())head = tail = mn = NULL;
        else adjust();
        
        return v;
    }
    
    T top(){
        if(empty())return T();
        return mn -> value;
    }
    
    void changeKey(Node *node, T x){
        if(func(node -> value, x))return;
        node -> value = x;
        if(func(x, mn -> value))mn = node;
        if(node -> par && func(node -> value, node -> par -> value))separate(node);
    }
    
    void remove(Node *node){
        separate(node);
        Node *h =  node -> cHead;
        Node *t = node -> cTail;
        for(auto x = h; x; x = x -> nxt)x -> par = NULL;
        merge(h, t);
        if(node -> prv)node -> prv -> nxt = node -> nxt;
        else head = node -> nxt;
        if(node -> nxt)node -> nxt -> prv = node -> prv;
        else tail = node -> prv;
        
        delete node;
        sz--;
        
        if(empty())head = tail = mn = NULL;
        else adjust();
    }
    
    size_t size(){
        return sz;
    }
    
    void clear(){
        while(head){
            head -> clear();
            Node *t = head -> nxt;
            delete head;
            head = t;
        }
    }
    ~FibonacciHeap(){
        clear();
    }
};

int main(){
    FibonacciHeap<int> f;
    f.push(10);
    f.push(5);
    auto x = f.push(20);
    f.push(500);
    f.changeKey(x, 1);
    cout << f.pop() << endl;
    cout << f.pop() << endl;
    cout << f.pop() << endl;
}
