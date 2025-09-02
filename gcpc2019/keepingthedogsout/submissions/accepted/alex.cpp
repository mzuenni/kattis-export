#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
#define FOR(i,a,b) for (int i = (a); i < (b); i++)

int main(){
    int N;
    cin >> N;
    vector<ll> num(++N);
    FOR(i,0,N)cin >> num[i];
    ll area = 0;
    FOR(i,0,N)area += num[i] << (2*i);
    for(ll wi = 1; wi * wi <= area; ++wi){
        if(area % wi)continue;
        ll remaining = 0;
        ll w = wi, h = area / wi;
        bool ok = true;
        for(int i = 0; i < N || remaining > 0; i++){
            if(i < N)remaining += num[i];
            if(w&1)remaining -= h;
            w-=w&1;
            if(h&1)remaining -= w;
            if(remaining < 0 || (remaining % 4) != 0){
                ok = false;
                break;
            }
            remaining /= 4;
            w/=2;
            h/=2;
        }
        if(ok){
            cout << wi << " " << (area / wi) << endl;
            assert(remaining == 0 && (w == 0 || h == 0));
            return 0;
        }
    }
    cout << "impossible\n";
    return 0;
}
