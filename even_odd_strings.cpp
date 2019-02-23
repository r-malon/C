#include <cmath>
#include <cstdio>
#include <iostream>
using namespace std;

int main(){
    int t;
    string s;
    cin >> t;
    string arr[t];
    for(int i=0;i<t;i++){
        cin >> s;
        arr[i]=s;
    }
    for(auto c: arr){
        for(int i=0;i<c.size();i+=2){
            cout << c[i];
        }
        cout << " ";
        for(int i=1;i<c.size();i+=2){
           cout << c[i];
        }
        cout << "\n";
    }
    return 0;
}
