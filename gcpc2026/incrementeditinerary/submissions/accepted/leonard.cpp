#include <algorithm>
#include <iostream>
#include <queue>
#include <vector>

const int INF = 100000005;

int main() {
	int n, m;
	std::cin >> n >> m;

	std::vector<std::vector<int>> graph(n + 1);

	for (int i = 0; i < m; ++i) {
		int a, b;
		std::cin >> a >> b;
		graph[a].push_back(b);
		graph[b].push_back(a);
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

	for (int v = 1; v <= n; ++v) {
		for (int u : graph[v]) {
			if (dist1[v] + 1 + distN[u] == dist1[n] + 1) {
				std::cout << "possible" << '\n';
				return 0;
			}
		}
	}

	std::cout << "impossible" << '\n';

	return 0;
}

