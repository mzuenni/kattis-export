#include <bits/stdc++.h>
using namespace std;
#define rep(i, n) for (int i = 0; i < n; i++)
struct UnionFind {
    vector<int> p;
    UnionFind(int n) : p(n, -1) {}
    int find(int x) {
        return p[x] < 0 ? x : p[x] = find(p[x]);
    }
    bool join(int x, int y) {
        while (p[x] > p[y = find(y)]) swap(x, y);
        return x != y && (p[x] += exchange(p[y], x));
    }
};
// Probably wrong since I didn't test, but this is about what I imagine a solution should look like.
// UnionFind, Bipartite Check, Some Handling of adjacency lists / visited so that time points don't look at O(n) space
int main() {
    cin.tie(0)->sync_with_stdio(0);
    int n, m;
    cin >> n >> m;
    UnionFind uf(n);
    map<int,vector<int>> prophecies; // neighboring ints are edges
    rep(i, m) {
        int u, v, t;
        cin >> u >> v >> t;
        for (int x : {u, v})
            prophecies[t].emplace_back(--x);
    }
    vector<vector<int>> adj(n);
    vector<int> vis(n);
    int ans = 0; // Shouldn't overflow since O(n log n) by standard smaller to larger argument
    for (auto &a : prophecies | views::values | views::reverse) {
        for (auto &u : a) u = uf.find(u);
        rep(i, size(a)) adj[a[i]].push_back(a[i ^ 1]);
        for (auto u : a) if (!vis[u]++) {
            array<int,2> c{};
            for (queue<int> q{{u}}; !empty(q); c[vis[u] - 1]++, q.pop())
                for (int v : adj[u = q.front()]) {
                    if (!vis[v])
                        vis[v] = 3 - vis[u], q.push(v), uf.join(u, v);
                    else if (vis[v] + vis[u] != 3)
                        cout << "impossible\n", exit(0);
                }
            ans += min(c[0], c[1]);
        }
        for (auto u : a) adj[u].clear(), vis[u] = 0;
    }
    cout << "possible\n" << ans << '\n';
}
