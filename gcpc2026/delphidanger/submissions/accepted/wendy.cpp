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

ll bfs(map<ll, vl> &adj) {
    queue<ll> q;
    map<ll, ll> seen;
    ll res = 0;
    for (auto x : adj) {
        if (seen.count(x.first) != 0) continue;
        q.push(x.first);
        seen[x.first] = 0;
        vl c(2, 0);
        c[0] += s[find(x.first)];
        while (!q.empty()) {
            ll v = q.front();
            q.pop();
            for (ll neigh : adj[v]) {
                if (seen.count(neigh) == 0) {
                    q.push(neigh);
                    seen[neigh] = 1 - seen[v];
                    c[seen[neigh]] += s[find(neigh)];
                }
                else if (seen[neigh] == seen[v]) return -1;
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
    map<ll, vector<pl>> times;
    for0(i, m) {
        cin >> u >> v >> t;
        u--; v--;
        times[-t].pb({u, v});
    }
    ll res = 0;
    for (auto [_, edges] : times) {
        map<ll, vl> adj;
        for (auto [u, v] : edges) {
            if (find(u) == find(v)) {
                cout << "impossible" << endl;
                return 0;
            }
            adj[find(u)].pb(find(v));
            adj[find(v)].pb(find(u));
        }
        ll c = bfs(adj);
        if (c == -1) {
            cout << "impossible" << endl;
            return 0;
        }
        res += c;
        for (auto [u, v] : edges) uni(u, v);
    }
    cout << "possible\n" << res << endl;

}
