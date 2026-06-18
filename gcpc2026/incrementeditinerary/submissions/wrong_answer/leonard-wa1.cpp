// only look for vertices with d(s, v) + d(v, t) = d(s, t) + 1

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

	std::vector<int> dist1(n + 1, INF), pre1(n + 1, -1);
	std::vector<int> distN(n + 1, INF), preN(n + 1, -1);

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
					pre1[u] = v;
					que.push(u);
				}
			}
		}
		std::swap(dist1, distN);
		std::swap(pre1, preN);
	}

	for (int v = 1; v <= n; ++v) {
		if (dist1[v] + distN[v] == dist1[n] + 1) {
			std::cout << "possible" << '\n';
			return 0;
		}
	}

	std::cout << "impossible" << '\n';

	return 0;
}

