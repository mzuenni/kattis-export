#include <iostream>
#include <vector>
#include <array>
using namespace std;

int main() {
    int n; cin >> n;
    vector<vector<array<int,2>>> tree(n);
    for(int i=0;i<n-1;++i) {
        int u,v,w; cin >> u >> v >> w;
        --u,--v;
        tree[u].push_back({v,w});
        tree[v].push_back({u,w});
    }
    vector<int> par(n);
    for(int i=0;i<n;++i) par[i]=i;
    auto find = [&](int at) {
        while(at!=par[at]) {
            par[at] = par[par[at]];
            at = par[at];
        }
        return at;
    };
    vector<int> deg(n);
    int m; cin >> m;
    for(int i=0;i<m*2;++i) {
        int u; cin >> u;
        deg[u-1]++;
    }
    long long length = 0;
    auto dfs = [&](auto&& self, int at, int from) -> bool {
        // parity
        bool ans = deg[at]%2;
        for(auto [to,w] : tree[at]) if(to!=from) {
            if(self(self,to,at)) {
                ans^=1;
                length += w;
            }
        }
        return ans;
    };
    dfs(dfs,0,-1);
    cout << length << '\n';

}