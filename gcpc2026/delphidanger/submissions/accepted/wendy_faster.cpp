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

vl s, parent;

void init(ll n) {
    s.resize(n, 1);
    parent.resize(n);
    for0(i, n) parent[i] = i;
}

ll find(ll i) {
    if (parent[i] == i) return i;
    ll p = find(parent[i]);
    parent[i] = p;
    return p;
}

void uni(ll i, ll j) {
    ll pi = find(i);
    ll pj = find(j);
    if (pi == pj) return;
    if (s[pi] < s[pj]) swap(pi, pj);
    parent[pj] = pi;
    s[pi] += s[pj];
}

vl seen, colors;

ll bfs(vector<vl> &adj, vl &active, ll i) {
    queue<ll> q;
    ll res = 0;
    for (ll x : active) {
        if (seen[x] == i) continue;
        q.push(x);
        seen[x] = i;
        colors[x] = 0;
        vl c(2, 0);
        c[0] += s[find(x)];
        while (!q.empty()) {
            ll v = q.front();
            q.pop();
            for (ll neigh : adj[v]) {
                if (seen[neigh] != i) {
                    q.push(neigh);
                    seen[neigh] = i;
                    colors[neigh] = 1 - colors[v];
                    c[colors[neigh]] += s[find(neigh)];
                }
                else if (colors[neigh] == colors[v]) return -1;
            }
        }
        res += min(c[0], c[1]);
    }
    return res;
}

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);
    ll n, m, u, v, t;
    cin >> n >> m;
    init(n);
    colors.resize(n);
    seen.resize(n, -1);
    map<ll, vector<pl>> times;
    for0(i, m) {
        cin >> u >> v >> t;
        u--; v--;
        times[-t].pb({u, v});
    }
    ll res = 0;
    vector<vl> adj(n);
    ll z = 0;
    for (auto [_, edges] : times) {
        vl active;
        for (auto [u, v] : edges) {
            if (find(u) == find(v)) {
                cout << "impossible" << endl;
                return 0;
            }
            active.pb(find(u));
            active.pb(find(v));
            adj[find(u)].pb(find(v));
            adj[find(v)].pb(find(u));
        }
        ll c = bfs(adj, active, z);
        if (c == -1) {
            cout << "impossible" << endl;
            return 0;
        }
        res += c;
        for (ll x : active) adj[x].clear();
        for (auto [u, v] : edges) uni(u, v);
        z++;
    }
    cout << "possible\n" << res << endl;

}
