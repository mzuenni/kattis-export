#include <bits/stdc++.h>
using namespace std;
using i64 = long long;

vector<i64> dijkstra(vector<vector<pair<int,i64>>> adj, int s) {
	vector<i64> dist(adj.size(), 1e18);
	set<pair<i64,int>> q;
	dist[s] = 0;
	q.insert({0,s});
	while (!q.empty()) {
		int i = begin(q)->second;
		q.erase(begin(q));
		for (const auto &[j, len]: adj[i]) {
			if (dist[j] <= dist[i]+len) continue;
			q.erase({dist[j],j});
			dist[j] = dist[i]+len;
			q.insert({dist[j],j});
		}
	}
	return dist;
}

int main() {
    int n, m, k;
    cin >> n >> m >> k;

    vector<vector<pair<int,i64>>> adj(n);
    while (m--) {
        int a, b, c;
        cin >> a >> b >> c;
        a--, b--;
        adj[a].emplace_back(b, c);
        adj[b].emplace_back(a, c);
    }

    auto ds = dijkstra(adj, 0);
    auto dt = dijkstra(adj, n-1);

    vector<pair<i64,double>> stores(k);
    for (auto &[d, p]: stores) {
        int i;
        cin >> i >> p;
        i--;
        d = ds[i] + dt[i];
    }
    sort(begin(stores), end(stores));

    double q = 1, res = 0;
    bool can = false;
    for (const auto &[d, p]: stores) {
        if (d >= 1e18) break;
        res += q*p*d;
        q *= 1-p;
    }
    if (q == 0) can = true;

    if (can) cout << fixed << setprecision(20) << res << '\n';
    else cout << "impossible" << '\n';
}
