#include <bits/stdc++.h>
using namespace std;

const double eps = 1e-9;

int main() {
	int n, m; cin >> n >> m;

	vector<vector<pair<int,double>>> adj(n);

	while (m--) {
		int a, b; double w;
		cin >> a >> b >> w;
		a--, b--;
		adj[a].emplace_back(b,log(w));
	}
	
	vector<double> dist(n);
	
	bool changed = false;
	for (int t = 0; t < n; t++) {
		changed = false;
		
		for (int i = 0; i < n; i++) {
			for (auto e: adj[i]) {
				int j; double len;
				tie(j,len) = e;
				if (dist[j] < dist[i] + len - eps) {
					dist[j] = dist[i] + len;
					changed = true;
				}
			}
		}
	}
	
	cout << (changed ? "inadmissible" : "admissible") << endl;
}
