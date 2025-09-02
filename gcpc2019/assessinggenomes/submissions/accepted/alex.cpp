#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
#define sz(c) int((c).size())
#define all(c) (c).begin(), (c).end()
#define FOR(i,a,b) for (int i = (a); i < (b); i++)

vector<int> getit(int N){
    vector<int> res(N);
    FOR(n,0,N){
        string in;
        cin >> in;
        int L = res[n] = sz(in);
        FOR(l,1,L){
            if(L%l)continue;
            bool ok = true;
            FOR(i,0,L-l)ok &= (in[i] == in[i+l]);
            if(ok){
                res[n] = l;
                break;
            }
        }
    }
    sort(all(res));
    return res;
}

int main(){
    int N;
    cin >> N;
    auto v1 = getit(N);
    auto v2 = getit(N);
    ll res = 0;
    FOR(i,0,sz(v1))res += (v1[i]-v2[i])*(v1[i]-v2[i]);
    cout << res << endl;
    return 0;
}
