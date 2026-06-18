#include <bits/stdc++.h>
using namespace std;
using ll = int64_t;
#define all(x) ::begin(x), ::end(x)
#define debug(x...) [](auto&& ...y){ cerr << "["#x"]:"; ((cerr << ' ' << y), ...) << endl; }(x)

struct Union {
    vector<int> a;

    Union(int n) : a(n, -1) {}

    int find(int i) {
        return a[i] < 0 ? i : find(a[i]);
    }

    void join(int i, int j) {
        i = find(i), j = find(j);
        if (i == j) return;
        swap(i, j);
        a[i] += a[j];
        a[j] = i;
    }

    int size(int i) {
        return -a[find(i)];
    }
};

int main() {
    cin.tie(0)->sync_with_stdio(0);

    int n, m;
    cin >> n >> m;
    map<int, vector<pair<int, int>>> mp;
    for (int i=0; i<m; i++) {
        int u, v, t;
        cin >> u >> v >> t;
        mp[-t].emplace_back(u-1, v-1);
    }

    Union un(n);
    vector<int> col(n, -1);
    vector<vector<int>> g(n);

    auto dfs = [&](auto& self, int u) -> array<int, 2> {
        array<int, 2> cnt = {un.size(u), 0};
        for (int v : g[u]) {
            if (col[v] == -1) {
                col[v] = !col[u];
                auto res = self(self, v);
                un.join(u, v);
                cnt[0] += res[1], cnt[1] += res[0];
            } else if (col[v] == col[u]) {
                cout << "impossible\n";
                exit(0);
            }
        }
        return cnt;
    };

    ll ans = 0;
    for (auto& [_, vec] : mp) {
        vector<int> us;
        for (auto& [u, v] : vec)  {
            u = un.find(u), v = un.find(v);
            if (u == v) {
                cout << "impossible\n";
                return 0;
            }
            us.push_back(u), us.push_back(v);
            g[u] = g[v] = {};
            col[u] = col[v] = -1;
        }
        for (auto [u, v] : vec) g[u].push_back(v), g[v].push_back(u);

        for (int u : us) if (col[u] == -1) {
            col[u] = 0;
            auto res = dfs(dfs, u);
            ans += min(res[0], res[1]);
        }
    }
    cout << "possible\n" << ans << '\n';
}
