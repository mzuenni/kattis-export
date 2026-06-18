#include <bits/stdc++.h>
using namespace std;
using ll = int64_t;
#define all(x) ::begin(x), ::end(x)
#define debug(x...) [](auto&& ...y){ cerr << "["#x"]:"; ((cerr << ' ' << y), ...) << endl; }(x)

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
        g[v].push_back(u);
    }

    vector<int> d1(n, -1), d2(n, -1);
    for (int s : {0, n-1}) {
        queue<int> q{{s}};
        d1[s] = 0;
        vector<bool> vis(n);
        while (!q.empty()) {
            int u = q.front();
            q.pop();
            vis[u] = true;
            for (int v : g[u]) if (!vis[v]) {
                if(d1[v] == -1) d1[v] = d1[u] + 1;
                q.push(v);
            }
        }
        swap(d1, d2);
    }

    for (int u=0; u<n; u++) {
        for (int v : g[u]) {
            if (d1[u] + d2[v] == d1[n-1]) {
                cout << "possible\n";
                return 0;
            }
        }
    }
    cout << "impossible\n";
}
