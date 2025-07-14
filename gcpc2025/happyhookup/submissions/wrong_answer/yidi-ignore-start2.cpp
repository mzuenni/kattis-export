#include <bits/stdc++.h>
using namespace std;
using ll = long long;
#define all(x) ::begin(x), ::end(x)
void _d(auto... x) { ((cerr << ' ' << x), ...) << endl; }
#define debug(x...) cerr << "["#x"]:", _d(x)

int main() {
    cin.tie(0)->sync_with_stdio(0);

    int n, m;
    cin >> n >> m;
    vector<vector<int>> g(n);
    for (int i=0; i<m; i++) {
        int u, v;
        cin >> u >> v;
        u--, v--;
        g[u].push_back(v);
    }

    int s1, s2;
    cin >> s1 >> s2;
    s1--, s2--;
    vector<int> vis(n);
    auto dfs = [&](auto& self, int u, int bit) {
        if (vis[u] & bit) return;
        vis[u] |= bit;
        if (vis[u] == 3 && u != s2) {
            cout << "yes " << u+1 << '\n';
            exit(0);
        }
        for (int v : g[u]) self(self, v, bit);
    };
    dfs(dfs, s1, 1);
    dfs(dfs, s2, 2);
    cout << "No\n";
}
