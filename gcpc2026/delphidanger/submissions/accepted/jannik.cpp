#include <algorithm>
#include <iostream>
#include <map>
#include <numeric>
#include <vector>

using namespace std;

#define all(a) (a).begin(), (a).end()
#define sz(a) ((int)(a).size())

using pii = pair<int, int>;

struct uf_t {
	vector<int> pa, csz;
	uf_t(int n) : pa(n), csz(n, 1) { iota(all(pa), 0); }
	int find(int i) { return pa[i] == i ? i : pa[i] = find(pa[i]); }
	void uunion(int i, int j)
	{
		i = find(i), j = find(j);
		if (i == j) return;
		csz[j] += csz[i];
		pa[i] = j;
	}
};

void fail()
{
	cout << "impossible\n";
	exit(0);
}

int main()
{
	int n, m;
	cin >> n >> m;
	vector<pair<int, pii>> edges(m);
	for (auto&[t,uv] : edges) {
		cin >> uv.first >> uv.second >> t;
		uv.first--, uv.second--;
	}
	sort(all(edges), greater<>{});

	uf_t uf(n);
	long res = 0;
	for (int i = 0; i < m; ) {
		int j = i + 1;
		vector<pii> es;
		map<int, vector<int>> adj;
		es.emplace_back(edges[i].second);
		while (j < m and edges[i].first == edges[j].first)
			es.emplace_back(edges[j++].second);
		i = j;
		for (auto&[u,v] : es) {
			u = uf.find(u), v = uf.find(v);
			if (u == v) fail();
			adj[u].emplace_back(v), adj[v].emplace_back(u);
		}
		map<int, int> colour;
		int csz[2] = {0, 0};
		const auto dfs = [&](auto&& self, int i, int c) -> void {
			auto[it, succ] = colour.emplace(i, c);
			if (not succ and c != it->second)
				fail();
			if (not succ)
				return;
			csz[c] += uf.csz[uf.find(i)];
			for (int j : adj[i])
				self(self, j, 1 - c);
		};
		for (const auto&[i,_] : adj)
			if (not colour.contains(i)) {
				csz[0] = 0, csz[1] = 0;
				dfs(dfs, i, 0);
				res += min(csz[0], csz[1]);
			}
		for (auto[u,v] : es)
			uf.uunion(u, v);
	}
	cout << "possible\n" << res << '\n';
}
