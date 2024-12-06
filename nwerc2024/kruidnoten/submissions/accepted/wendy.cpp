#include <vector>
#include <queue>
#include <iostream>
#include <algorithm>
#include <iomanip>

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

ll INF = (ll) 1e18;

vl dijkstra(vector<vector<pl>> &adj, ll s) {
    vl dist(sz(adj), INF);
    dist[s] = 0;
    priority_queue<pl, vector<pl>, greater<pl>> q;
    q.push({0, s});
    while (!q.empty()) {
        pl cur = q.top();
        q.pop();
        if (cur.first != dist[cur.second]) continue;
        for (auto e : adj[cur.second]) {
            if (dist[cur.second] + e.first < dist[e.second]) {
                dist[e.second] = dist[cur.second] + e.first;
                q.push({dist[e.second], e.second});
            }
        }
    }
    return dist;
}

int main() {
    ios_base::sync_with_stdio(false);
	cin.tie(nullptr);

    ll n, m, k, a, b, w;
    cin >> n >> m >> k;
    vector<vector<pl>> adj(n);
    vector<pair<ll, ld>> via(n, {0, -1.0});
    for0(i, m) {
        cin >> a >> b >> w;
        adj[a - 1].pb({w, b - 1});
        adj[b - 1].pb({w, a - 1});
    }
    for0(i, k) cin >> a >> via[a - 1].second;
    vl ds = dijkstra(adj, 0);
    vl dt = dijkstra (adj, n - 1);

    for0(i, n) via[i].first = min(INF, ds[i] + dt[i]);
    sort(via.begin(), via.end());

    ld exp = 0;
    bool one = false;
    for (int i = n - 1; i >= 0; i--) {
        if (via[i].second < 0.0 || via[i].first == INF) continue;
        if (via[i].second == 1.0) one = true;
        exp = (1.0 - via[i].second) * exp + via[i].first * via[i].second;
    }
    if (one) cout << fixed << setprecision(10) << exp << endl;
    else cout << "impossible" << endl;
}