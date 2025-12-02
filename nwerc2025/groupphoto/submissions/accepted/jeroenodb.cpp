#include "bits/stdc++.h"
using namespace std;
typedef vector<int> vi;
typedef array<int,2> pt;

int main() {
    cin.tie(NULL)->sync_with_stdio(false);
    int n; cin >> n;
    vi a(n);
    for(auto& i : a) cin >> i,i=n-i;
    vector<pt> ps;
    for(int i=0;i<n;++i) {
        for(int id=0;auto [l,r] : {pt{i,1+a[i]+i},{i-a[i],i+1}}) {
            if(0<=l and r<=n) {
                ps.push_back({l*2 + (!id) ,-(r*2 - (id))});
            }
            if(a[i]==0) break;
            id++;
        }
    }
    sort(begin(ps),end(ps));
    vi dp;
    for(auto [l,r] : ps) {
        auto it = upper_bound(begin(dp),end(dp),r);
        if(it==dp.end()) dp.push_back(r);
        else *it=r;
    }
    cout << n-dp.size() << '\n';
}