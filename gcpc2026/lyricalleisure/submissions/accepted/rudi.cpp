#include<bits/stdc++.h>
using namespace std;

int main(){
    int n, k;
    cin >> n >> k;

    string s = "";

    for(int i=0; i<k; i++){
        s += 'a';
    }
    for(int i=k; i<n; i++){
        s += (i%3 == 0) ? 'b' : (i%3 == 1) ? 'c' : 'd';
    }
    cout << s << endl;
}