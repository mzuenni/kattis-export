#include <bits/stdc++.h>
using namespace std;
using i64 = long long;

int main() {
	int n, m, k;
	cin >> n >> m >> k;

	vector<map<int, int>> outdeg(n);
	vector<vector<tuple<int,int,int>>> rev_adj(n);
	while (m--) {
		int a, b, len;
		cin >> a >> b >> len >> k;
		a--, b--;
		while (k--) {
			int col; cin >> col;
			outdeg[a][col]++;
			rev_adj[b].emplace_back(col, a, len);
		}
	}
	
	vector<i64> dist(n, 1e16);
	set<tuple<i64,int,int>> pq;
	pq.emplace(0,-1,n-1);

	while (!pq.empty()) {
		auto [col_dist, col, a] = *begin(pq);
		pq.erase(begin(pq));
		if (--outdeg[a][col] > 0 || col_dist >= dist[a]) continue;
		dist[a] = col_dist;
		
		for (auto [col, b, len]: rev_adj[a]) {
			pq.emplace(dist[a]+len, col, b);
		}
	}
	
	if (dist[0] < 1e16) cout << dist[0] << endl;
	else cout << "impossible" << endl;
}
