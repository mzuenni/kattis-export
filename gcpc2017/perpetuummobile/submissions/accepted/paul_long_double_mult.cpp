#include <bits/stdc++.h>
using namespace std;

typedef long double dbl;

int main() {
	int n, m; cin >> n >> m;

	vector<vector<pair<int,dbl>>> adj(n);

	while (m--) {
		int a, b; dbl w;
		cin >> a >> b >> w;
		a--, b--;
		adj[a].emplace_back(b,w);
	}
	
	vector<dbl> dist(n,1);
	
	bool changed = false;
	for (int t = 0; t < n; t++) {
		changed = false;
		
		vector<dbl> ndist = dist;
		for (int i = 0; i < n; i++) {
			for (auto e: adj[i]) {
				int j; dbl len;
				tie(j,len) = e;
				if (ndist[j] < dist[i] * len) {
					ndist[j] = dist[i] * len;
					changed = true;
				}
			}
		}
		dist = ndist;
	}
	
	cout << (changed ? "inadmissible" : "admissible") << endl;
}
