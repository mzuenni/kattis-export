#include <bits/stdc++.h>
#define f(i, s, k, l) for (int i = s; i < k; i += l)
#define for0(i, k) f(i, 0, k, 1)

#define pl pair<long long, long long>
#define pb push_back

#define vl vector<long long>
#define vi vector<int>
#define sz(x) (ll)(x).size()

using namespace std;
using ll = long long;
using ld = long double;

ll bfs(vector<vl> &adj, vl &vis, ll s, ll pass) {
    queue<ll> q;
    q.push(s);
    if (vis[s] + pass == 3) return s;
    vis[s] = pass;
    while (!q.empty()) {
        ll v = q.front();
        q.pop();
        for (ll neigh : adj[v]) {
            if (vis[neigh] + pass == 3) return neigh;
            if (vis[neigh] == pass) continue;
            q.push(neigh);
            vis[neigh] = pass;
        }
    }
    return -1;
}

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);
    ll n, m, x, y, a, b;
    cin >> n >> m;
    vector<vl> adj(n);
    for0(i, m) {
        cin >> x >> y;
        x--; y--;
        adj[x].pb(y);
    }
    cin >> a >> b;
    vl vis(n, 0);
    bfs(adj, vis, a - 1, 1);
    ll res = bfs(adj, vis, b - 1, 2);
    if (res > 0) {
        cout << "yes" << endl;
        cout << res + 1 << endl;
    } else cout << "no" << endl;
}