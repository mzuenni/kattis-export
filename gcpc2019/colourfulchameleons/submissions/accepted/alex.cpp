#include <bits/stdc++.h>
using namespace std;

#define FOR(i,a,b) for (int i = (a); i < (b); i++)
typedef long long ll;

ll N,C,Y, v[(int)1.1e5];
int main(){
    cin >> N >> C >> Y;
    FOR(i,0,N)cin >> v[i];
    swap(v[N-1],v[C-1]);
    ll maxi = v[0];
    FOR(i,0,N-1)maxi = max(maxi, v[i]);
    ++Y;
    ll need = 0;
    FOR(i,0,N-1){
        ll diff = maxi - v[i];
        if(diff % Y != 0){
            cout << "impossible\n";
            return 0;
        }
        need += diff / Y;
    }
    cout << maxi << " " << v[N-1] - maxi + Y * (maxi - need) << endl;
    return 0;
}
