#include <bits/stdc++.h>
using namespace std;

int main() {
	int n, m; cin >> n >> m;
	vector<array<int, 3>> e(m);
	for (int i = 0; i < m; i++) {
		int u, v, t; cin >> u >> v >> t;
		u--, v--;
		e[i] = {t, u, v};
	}
	sort(e.rbegin(), e.rend());

	int ans = 0;
	vector<int> vis(n), comp(n), col(n);
	vector<array<int, 2>> s(n);
	vector<vector<int>> g(n);

	fill(s.begin(), s.end(), array<int,2>{1, 0});
	iota(comp.begin(), comp.end(), 0);

	function<int(int)> qry = [&](int x) {
		return x == comp[x] ? x : comp[x] = qry(comp[x]);
	};

	function<bool(int)> dfs = [&](int u) {
		vis[u] = 1;
		bool res = true;
		for (int v: g[u]) {
			if (!vis[v]) {
				col[v] = !col[u];
				res &= dfs(v);
			} else if (col[u] == col[v])
				res = false;
		}
		return res;
	};

	bool possible = true;
	for (int i = 0, j = 0; i < m; i = j) {
		while (j < m && e[j][0] == e[i][0])
			j++;
		for (int k = i; k < j; k++) {
			for (int u: {e[k][1], e[k][2]}) {
				u = qry(u);
				g[u].clear();
				vis[u] = 0;
			}
		}
		set<int> nodes;
		for (int k = i; k < j; k++) {
			auto [_, u, v] = e[k];
			u = qry(u);
			v = qry(v);
			g[u].push_back(v);
			g[v].push_back(u);
			nodes.insert(u);
			nodes.insert(v);
		}
		for (int k = i; k < j; k++) {
			auto [_, u, v] = e[k];
			u = qry(u);
			v = qry(v);
			comp[u] = v;
		}
		for (int u: nodes) {
			s[u][0] += s[u][1];
			s[u][1] = 0;
			if (u == qry(u)) {
				col[u] = 0;
				possible &= dfs(u);
			}
		}
		for (int u: nodes) {
			int c = qry(u);
			if (u != c)
				s[c][col[u]] += s[u][0];
		}
		for (int u: nodes) {
			if (u == qry(u))
				ans += min(s[u][0], s[u][1]);
		}
	}
	if (!possible)
		cout << "impossible\n";
	else
		cout << "possible\n" << ans << "\n";
}