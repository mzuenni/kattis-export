#include <bits/stdc++.h>
using namespace std;

#define FOR(i,a,b) for (int i = (a); i < (b); i++)

string IMP = "impossible";
bool first = true;
void rek(int f, int t, int d){
    assert(f < t);
    if(d+d-1 >= t-f){
        int x = f + d - 1;
        if(first)first = false;
        else cout << " ";
        cout << x;
        FOR(i,f,t)if(x != i)cout << " " << i;
    } else {
        int m = f + (t-f)/2;
        if(first)first = false;
        else cout << " ";
        cout << m;
        rek(f,m,d-1);
        rek(m+1,t,d-1);
    }
}
int main(){
    int N,K;
    cin >> N >> K;
    if(K < 20 && (1<<K) <= N){
        cout << IMP << endl;
        return 0;
    }
    rek(1,N+1, K);
    cout << endl;
    return 0;
}
