#include <bits/stdc++.h>
using namespace std;

typedef long double dbl;

int main() {
	int n, m; cin >> n >> m;
	
	vector<vector<dbl>> adj(n,vector<dbl>(n));

	while (m--) {
		int i, j; dbl w;
		cin >> i >> j >> w;
		i--, j--;
		adj[i][j] = max(adj[i][j], w);
	}
	
	for (int k = 0; k < n; k++) {
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < n; j++) {
				adj[i][j] = max(adj[i][j], adj[i][k]*adj[k][j]);
				if (i == j && adj[i][j] > 1) {
					cout << "inadmissible" << endl;
					return 0;
				}
			}
		}
	}
	cout << "admissible" << endl;
}
