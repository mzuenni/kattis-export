#include <bits/stdc++.h>
using namespace std;
using i64 = long long;

int main() {
	int n, m, k;
	cin >> n >> m >> k;

	vector<vector<pair<int,int>>> adj(n);
	while (m--) {
		int a, b, len;
		cin >> a >> b >> len >> k;
		a--, b--;
		adj[a].emplace_back(b, len);
		while (k--) {
			int col; cin >> col;
		}
	}
	
	vector<i64> dist(n, 1e16);
	set<pair<i64,int>> pq;
	pq.insert({0,0});

	while (!pq.empty()) {
		auto [d,a] = *begin(pq);
		pq.erase(begin(pq));
		
		for (auto [b,len]: adj[a]) {
			if (dist[b] < dist[a] + len) continue;
			pq.erase({dist[b],b});
			dist[b] = dist[a] + len;
			pq.insert({dist[b],b});
		}
	}
	
	if (dist[n-1] < 1e16) cout << dist[n-1] << endl;
	else cout << "impossible" << endl;
}
