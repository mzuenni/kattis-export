#include <bits/stdc++.h>

#define rep(a, b)   for(int a = 0; a < (b); ++a)
#define all(a)      (a).begin(),(a).end()
#define endl        '\n'

using namespace std;
using ll = long long;
using Graph = vector<vector<int>>;

void solve() {
    int n,m; cin>>n>>m;
    Graph g(n); // outgoing
    vector indeg(n,0);
    rep(i,m) {
        int a,b; cin>>a>>b; --a,--b;
        g[a].push_back(b);
        indeg[b]++;
    }
    vector<int> order;
    rep(i,n) if(!indeg[i]) order.push_back(i);
    bool missing = false;
    int done = 0;
    for(; done<size(order); ++done) {
        missing |= size(order)-done>1;
        for(auto nei : g[order[done]]) if(!--indeg[nei]) order.push_back(nei);
    }
    if(done< n) { cout << "recheck hints" << endl; return; }
    if(missing) { cout << "missing hints" << endl; return; }
    rep(i,n) cout << order[i]+1 << " \n"[i==n-1];
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t; cin>>t;
    while(t--) solve();

    return 0;
}