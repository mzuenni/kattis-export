#include <bits/stdc++.h>
using namespace std;
using ll = int64_t;
#define all(x) ::begin(x), ::end(x)
void _d(auto... x) { ((cerr << ' ' << x), ...) << endl; }
#define debug(x...) cerr << "["#x"]:", _d(x)

constexpr int N = 1e5 + 5;
using bs = bitset<N>;

int main() {
    cin.tie(0)->sync_with_stdio(0);

    int n;
    cin >> n;
    vector<vector<pair<int, int>>> g(n);
    vector<int> ws(n);
    for (int i=0; i<n-1; i++) {
        int u, v;
        cin >> u >> v >> ws[i];
        u--, v--;
        g[u].emplace_back(v, i);
        g[v].emplace_back(u, i);
    }

    vector<bs> b(n);
    auto dfs = [&](auto& self, int u, int p) -> void {
        for (auto [v, w] : g[u]) if (v != p) {
            b[v] = b[u];
            b[v][w] = 1;
            self(self, v, u);
        }
    };
    dfs(dfs, 0, 0);

    int m;
    cin >> m;
    vector<char> a(n);
    for (int i=0; i<m; i++) {
        int u, v;
        cin >> u >> v;
        u--, v--;
        a[u] ^= 1;
        a[v] ^= 1;
    }

    bs sol;
    for (int i=0; i<n; i++) if (a[i]) sol ^= b[i];

    ll ans = 0;
    for (int i=0; i<n; i++) if (sol[i]) ans += ws[i];
    cout << ans << '\n';
}
