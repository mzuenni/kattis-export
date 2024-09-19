#include <bits/stdc++.h>
using namespace std;

const int N = 1e6 + 10;
vector<int> adj[N];
int col[N];
bool two_col = true; 

void dfs(int i, int p) {
	for (int j: adj[i]) if (j != p) {
		if (col[j] == -1) {
			col[j] = 1-col[i];
			dfs(j,i);
		}
		if (col[j] == col[i]) two_col = false;
	}
}

int main() {
	int n, m, p;
	cin >> n >> m >> p;

	memset(col,-1,sizeof col);
	
	while (m--) {
		int a, b;
		cin >> a >> b;
		adj[a].push_back(b);
		adj[b].push_back(a);
	}

	int res = 1;
	for (int i = 1; i <= n; i++) if (col[i] == -1) {
		col[i] = 0;
		dfs(i,-1);	
		if (i > 1) res = 2*res % p;
	}
	res = (res+1) % p;

	if (two_col) cout << res << endl;
	else cout << "impossible" << endl;
}
