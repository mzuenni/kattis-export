#include <algorithm>
#include <iostream>
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
		if (i != j) csz[j] += csz[i];
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
	ios::sync_with_stdio(false), cin.tie(nullptr);
	int n, m;
	cin >> n >> m;
	vector<pair<int, pii>> edges(m);
	for (auto&[t,uv] : edges) {
		cin >> uv.first >> uv.second >> t;
		uv.first--, uv.second--;
	}
	sort(all(edges), greater<>{});

	vector<vector<int>> adj(n);
	vector<int> colour(n);

	uf_t uf(n);
	long res = 0;
	for (int i = 0; i < m; ) {
		int j = i + 1;
		vector<pii> es;
		es.emplace_back(edges[i].second);
		while (j < m and edges[i].first == edges[j].first)
			es.emplace_back(edges[j++].second);
		i = j;
		for (auto&[u,v] : es) {
			u = uf.find(u), v = uf.find(v);
			if (u == v) fail();
			adj[u].emplace_back(v), adj[v].emplace_back(u);
			colour[u] = colour[v] = -1;
		}
		int csz[2] = {0, 0};
		const auto dfs = [&](auto&& self, int i, int c) -> void {
			if (colour[i] == c)
				return;
			if (colour[i] != -1)
				fail();
			colour[i] = c;
			csz[c] += uf.csz[i];
			for (int j : adj[i])
				self(self, j, 1 - c);
		};
		for (auto[u,v] : es) {
			if (colour[u] == -1) {
				csz[0] = 0, csz[1] = 0;
				dfs(dfs, u, 0);
				res += min(csz[0], csz[1]);
			}
			if (colour[v] == -1) {
				csz[0] = 0, csz[1] = 0;
				dfs(dfs, v, 0);
				res += min(csz[0], csz[1]);
			}
		}
		for (auto[u,v] : es) {
			uf.uunion(u, v);
			adj[u].clear(), adj[v].clear();
		}
	}
	cout << "possible\n" << res << '\n';
}
