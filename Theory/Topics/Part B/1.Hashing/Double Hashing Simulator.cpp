#include<bits/stdc++.h>
using namespace std;
int h1(int x){
    return 2 * x + 5;
}

int h2(int x){
    return 7 - x % 7;
}


int tab[100];

int main(){
    int m;
    cin >> m;
    memset(tab, -1, sizeof tab);
    
    for(int i = 0; i < m; i++){
        int x;
        cin >> x;
        int a = h1(x) % m;
        int b = h2(x);
        cout << "H1 -> " << a << endl;
        cout << "H2 -> " << b << endl;
        for(int j = 0; j < m; j++){
            if(tab[(a + j * b) % m] == -1){
                tab[(a + j * b) % m] = x;
                cout << "Inserted at -> " << (a + j * b) % m << endl;
                break;
            }
        }
        
        cout << "TABLE --> " << endl;
        for(int j = 0; j < m; j++){
            cout << setw(3) << j << "  ";
        }
        cout << endl;
        for(int j = 0; j < m; j++){
            cout << setw(3) << tab[j] << ", ";
        }
        cout << endl;
    }
    
}
