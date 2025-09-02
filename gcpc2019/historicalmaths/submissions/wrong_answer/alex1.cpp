#include <bits/stdc++.h>
using namespace std;

typedef __int128 ll;
#define sz(c) int((c).size())
#define FOR(i,a,b) for (int i = (a); i < (b); i++)
#define FORD(i,a,b) for (int i = int(b)-1; i >= (a); i--)

vector<ll> getnum(){
    int N;
    cin >> N;
    vector<ll> res(N);
    int tmp;
    FORD(i,0,N){
        cin >> tmp;
        res[i] = tmp;
    }
    return res;
}

int main(){
    auto a = getnum(), b = getnum();
    auto c = getnum();
    ll maxdigit = 1;
    //for(auto x:a)maxdigit = max(maxdigit, x);
    for(auto x:b)maxdigit = max(maxdigit, x);
    for(auto x:c)maxdigit = max(maxdigit, x);
    vector<ll> r(sz(a)+sz(b)-1);
    FOR(i,0,sz(a))FOR(j,0,sz(b))r[i+j] += a[i]*b[j];
    ll maxmul = 0;
    for(auto x: r)maxmul = max(maxmul, x);
    ll lo = maxdigit + 1;
    ll hi = maxmul + 1;
    while(lo <= hi){
        ll m = lo + (hi - lo) / 2;
        vector<ll> vg;
        ll last = 0;
        for(auto x: r){
            last += x;
            vg.push_back(last % m);
            last /= m;
        }
        while(last){
            vg.push_back(last % m);
            last /= m;
        }
        bool islarger = false;
        bool islower = false;
        if(sz(vg) != sz(c)){
            if(sz(vg) > sz(c))islarger = true;
            else islower = true;
        } else {
            FORD(i,0,sz(vg)){
                if(vg[i] != c[i]){
                    if(vg[i] > c[i])islarger = true;
                    else islower = true;
                    break;
                }
            }
        }
        if(islarger)lo = m + 1;
        else if(islower)hi = m - 1;
        else {
            if(m == maxmul + 1){
                FOR(i,0,1000)cout << 1;
                cout << endl;
            } else {
                cout << (long long)m << endl;
            }
            return 0;
        }
    }
    cout << "impossible\n";
    return 0;
}
