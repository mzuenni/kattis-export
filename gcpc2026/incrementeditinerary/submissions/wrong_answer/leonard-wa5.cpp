// Only check one orientation of the edges.
// That is, check if path(1, u) + path(v, n) is valid,
// but not if path(1, v) + path(u, n) is valid.

#include <algorithm>
#include <iostream>
#include <queue>
#include <vector>

const int INF = 100000005;

int main() {
	int n, m;
	std::cin >> n >> m;

	std::vector<std::vector<int>> graph(n + 1);
	std::vector<std::pair<int, int>> edges(m);

	for (int i = 0; i < m; ++i) {
		int u, v;
		std::cin >> u >> v;
		graph[u].push_back(v);
		graph[v].push_back(u);
		edges[i] = {u, v};
	}

	std::vector<int> dist1(n + 1, INF);
	std::vector<int> distN(n + 1, INF);

	for (int start : {1, n}) {
		dist1[start] = 0;
		std::queue<int> que;
		que.push(start);
		while (!que.empty()) {
			int v = que.front();
			que.pop();
			for (int u : graph[v]) {
				if (dist1[u] == INF) {
					dist1[u] = dist1[v] + 1;
					que.push(u);
				}
			}
		}
		std::swap(dist1, distN);
	}

	for (auto [u, v] : edges) {
		if (dist1[u] + 1 + distN[v] == dist1[n] + 1) {
			std::cout << "possible" << '\n';
			return 0;
		}
	}

	std::cout << "impossible" << '\n';

	return 0;
}

