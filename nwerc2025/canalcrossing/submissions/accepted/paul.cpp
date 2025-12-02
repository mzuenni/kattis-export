#include <bits/stdc++.h>
using namespace std;
using i64 = long long;

int main() {
    int n; cin >> n;
    vector<vector<pair<int,int>>> adj(n);
    for (int i = 1; i < n; i++) {
        int a, b, c;
        cin >> a >> b >> c;
        a--, b--;
        adj[a].emplace_back(b, c);
        adj[b].emplace_back(a, c);
    }

    vector<int> parity(n);

    int m; cin >> m;
    for (int i = 0; i < 2*m; i++) {
        int a; cin >> a;
        parity[a-1] ^= 1;
    }

    i64 res = 0;
    auto dfs = [&](const auto &self, int a, int p) -> void {
        for (auto [b, c]: adj[a]) if (b != p) {
            self(self, b, a);
            parity[a] ^= parity[b];
            if (parity[b]) res += c;
        }
    };
    dfs(dfs, 0, -1);
    cout << res << '\n';
}
