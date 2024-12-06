#include <algorithm>
#include <iostream>
#include <numeric>
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
	vector<vector<int>> g(n);
	for (int i = 0; i < m; i++) {
		int u, v;
		cin >> u >> v;
		u--; v--;
		g[u].push_back(v);
		g[v].push_back(u);
	}
	int check_bits = accumulate(a.begin(), a.end(), 0);
	if (check_bits == 0 || check_bits == n) {
		cout << 1 << endl;
		return 0;
	}

	vector<vector<int>> N(n, vector<int>(2, 0));
	for (int u = 0; u < n; u++) {
		for (int v: g[u]) N[u][a[v]]++;
	}
	
	vector<int> d(n, oo);
	queue<pair<int, int>> q;
	for (int u = 0; u < n; u++) if (N[u][0] == 0 || N[u][1] == 0) {
		q.emplace(u, 2);
	}
	while (!q.empty()) {
		auto [u, c] = q.front();
		q.pop();

		if (d[u] <= c) continue;
		d[u] = c;

		//int nxt = (a[u] == val ? (val+1)%2 : a[u]);
		//for (int v: g[u]) if (a[v] == nxt) {
		for (int v: g[u]) {
			if (d[v] == oo && --N[v][a[u]] == 0) q.emplace(v, c+1);
		}
	}

	//vector<vector<int>> r(2, vector<int>(2, 0));
	//for (int i = 0; i < n+2; i++) for (int j = 0; j < 2; j++)
	//	r[a[i]][j] = max(r[a[i]][j], d[i][j]);
	//int res = min({r[0][0], r[0][1], r[1][0], r[1][1]});
	int res = *max_element(d.begin(), d.end());;
	if (res < oo) cout << res << endl;
	else cout << "infinity" << endl;
	return 0;
}
