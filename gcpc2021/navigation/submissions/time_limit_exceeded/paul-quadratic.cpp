#include <bits/stdc++.h>
using namespace std;
using i64 = long long;

int main() {
	int n, m, k;
	cin >> n >> m >> k;

	vector<map<int,vector<pair<int,int>>>> adj(n);
	while (m--) {
		int a, b, len;
		cin >> a >> b >> len >> k;
		a--, b--;
		while (k--) {
			int col; cin >> col;
			adj[a][col].emplace_back(b, len);
		}
	}

	vector<i64> dist(n, 1e16);
	dist[n-1] = 0;

	bool go = true;
	while (go) {
		go = false;
		for (int a = 0; a < n; a++) {
			for (auto [col,v]: adj[a]) {
				i64 cur = 0;
				for (auto [b,len]: v) {
					cur = max(cur, dist[b]+len);
				}
				if (cur < dist[a]) {
					dist[a] = cur;
					go = true;
				}
			}
		}
	}
	
	if (dist[0] < 1e16) cout << dist[0] << endl;
	else cout << "impossible" << endl;
}
