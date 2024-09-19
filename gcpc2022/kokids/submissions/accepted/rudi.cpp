#include<bits/stdc++.h>
using namespace std;

int main(){
    int n, k;
    string s;
    cin >> n >> k >> s;
    bool goLeft = true;
    for(char c : s){
        if(goLeft == (c == 'L')) goLeft = !goLeft;
        else k--;
    }
    cout << max(0, k) << endl;
}