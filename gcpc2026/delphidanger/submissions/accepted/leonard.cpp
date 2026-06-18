#include <algorithm>
#include <array>
#include <iostream>
#include <vector>

struct DSU {
	std::vector<int> p;

	DSU(int n) : p(n, -1) {}

	int leader(int u) {
		return p[u] < 0 ? u : p[u] = leader(p[u]);
	}

	bool unite(int u, int v) {
		u = leader(u);
		v = leader(v);
		if (u == v) return false;
		if (p[u] > p[v]) std::swap(u, v);
		p[u] += p[v];
		p[v] = u;
		return true;
	}
};

int main() {
	int n, m;
	std::cin >> n >> m;

	std::vector<std::array<int, 3>> edges(m);

	for (auto& [t, u, v] : edges) {
		std::cin >> u >> v >> t;
		u -= 1;
		v -= 1;
	}

	std::sort(edges.rbegin(), edges.rend());

	std::vector<std::vector<int>> graph(n);
	std::vector<int> last(n, -1), col(n, -1), cnt(2);
	DSU dsu(n);

	long long ans = 0;

	for (int i = 0; i < m;) {
		std::vector<int> vs;
		int id = i;
		while (i < m && edges[i][0] == edges[id][0]) {
			auto [t, u, v] = edges[i];
			u = dsu.leader(u);
			v = dsu.leader(v);
			if (u == v) {
				std::cout << "impossible" << '\n';
				return 0;
			}
			if (last[u] != id) {
				vs.push_back(u);
				last[u] = id;
			}
			if (last[v] != id) {
				vs.push_back(v);
				last[v] = id;
			}
			graph[u].push_back(v);
			graph[v].push_back(u);
			i += 1;
		}
		for (int start : vs) {
			if (col[start] != -1) continue;
			cnt[0] = cnt[1] = 0;
			std::vector<int> st;
			st.push_back(start);
			col[start] = 0;
			cnt[0] = -dsu.p[start];
			while (!st.empty()) {
				int v = st.back();
				st.pop_back();
				for (int u : graph[v]) {
					if (col[u] == -1) {
						col[u] = col[v] ^ 1;
						cnt[col[u]] -= dsu.p[u];
						st.push_back(u);
					}
					if (col[u] == col[v]) {
						std::cout << "impossible\n";
						return 0;
					}
				}
			}
			ans += std::min(cnt[0], cnt[1]);
		}
		for (int v : vs) {
			for (int u : graph[v]) {
				dsu.unite(u, v);
			}
		}
		for (int v : vs) {
			graph[v].clear();
			col[v] = -1;
		}
	}

	std::cout << "possible\n" << ans << '\n';

	return 0;
}

