#include <algorithm>
#include <iostream>
#include <queue>
#include <vector>

using namespace std;
const int oo = 3 * 10e5 + 5;

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	
	int n, m;
	cin >> n >> m;
	vector<int> a(n);
	for (int &k: a) cin >> k;
	a.push_back(0);
	a.push_back(1);
	vector<vector<int>> g(n+2);
	for (int i = 0; i < m; i++) {
		int u, v;
		cin >> u >> v;
		u--; v--;
		g[u].push_back(v);
		g[v].push_back(u);
	}
	for (int i = 0; i < n; i++) {
		g[i].push_back(n);
		g[i].push_back(n+1);
		g[n].push_back(i);
		g[n+1].push_back(i);
	}

	vector<vector<int>> N(n, vector<int>(2, 0));
	for (int u = 0; u < n; u++) {
		for (int v: g[u]) N[u][a[v]]++;
	}
	
	vector<vector<int>> d(n+2, vector<int>(2, oo));
	queue<tuple<int, int, int>> q;
	for (int i = 0; i < 2; i++) {
		q.emplace(n, i, 1);
		q.emplace(n+1, i, 1);
	}
	while (!q.empty()) {
		auto [u, val, c] = q.front();
		q.pop();

		if (d[u][val] <= c) continue;
		d[u][val] = c;

		int nxt = (a[u] == val ? (val+1)%2 : a[u]);
		for (int v: g[u]) if (a[v] == nxt) {
			if (d[v][a[u]] == oo && --N[v][a[u]] == 0) q.emplace(v, a[u], c+1);
		}
	}

	vector<vector<int>> r(2, vector<int>(2, 0));
	for (int i = 0; i < n+2; i++) for (int j = 0; j < 2; j++)
		r[a[i]][j] = max(r[a[i]][j], d[i][j]);
	int res = min({r[0][0], r[0][1], r[1][0], r[1][1]});
	if (res < oo) cout << res << endl;
	else cout << "infinity" << endl;
	return 0;
}
