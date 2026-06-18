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
	vector<int> par(n), col(n);
	vector<pair<int, int>> sz(n, make_pair(1, 0));
	iota(par.begin(), par.end(), 0);
	set<int> vis;

	function<pair<int, int>(int)> qry = [&](int x) {
		if (x == par[x])
			return make_pair(x, col[x]);
		auto res = qry(par[x]);
		res.second ^= col[x];
		return res;
	};

	auto join = [&](int u, int v) {
		auto x = qry(u), y = qry(v);
		u = x.first, v = y.first;
		if (u == v)
			return x.second != y.second;
		vis.insert(u);
		vis.insert(v);
		// if (sz[u].first + sz[u].second > sz[v].first + sz[v].second)
		// 	swap(u, v);
		if (rand() % 2)
			swap(u, v);
		par[u] = v;
		if (x.second != y.second)
			swap(sz[u].first, sz[u].second);
		sz[v] = make_pair(sz[v].first + sz[u].second, sz[v].second + sz[u].first);
		col[u] = x.second ^ y.second ^ 1;
		return true;
	};

	int ans = 0;
	for (int i = 0, j = 0; i < m; i = j) {
		vis.clear();
		while (j < m && e[i][0] == e[j][0]) {
			e[j][1] = qry(e[j][1]).first;
			e[j][2] = qry(e[j][2]).first;
			j++;
		}
		for (; i < j; i++) {
			auto [_, u, v] = e[i];
			if (!join(u, v)) {
				cout << "impossible\n";
				return 0;
			}
		}
		for (int u: vis) {
			auto dat = qry(u);
			if (u == dat.first)
				ans += min(sz[u].first, sz[u].second);
			sz[u] = make_pair(sz[u].first + sz[u].second, 0);
			if (dat.second)
				swap(sz[u].first, sz[u].second);
		}
	}
	cout << "possible\n" << ans << "\n";
}