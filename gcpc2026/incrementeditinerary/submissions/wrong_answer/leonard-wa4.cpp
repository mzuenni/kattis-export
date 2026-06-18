// check if the component containing vertex 1 is bipartite

#include <iostream>
#include <queue>
#include <vector>

int main() {
	int n, m;
	std::cin >> n >> m;

	std::vector<std::vector<int>> graph(n);

	for (int i = 0; i < m; ++i) {
		int u, v;
		std::cin >> u >> v;
		u -= 1;
		v -= 1;
		graph[u].push_back(v);
		graph[v].push_back(u);
	}

	std::vector<int> col(n, -1);
	std::queue<int> que;

	col[0] = 0;
	que.push(0);

	while (!que.empty()) {
		int v = que.front();
		que.pop();
		for (int u : graph[v]) {
			if (col[u] == -1) {
				col[u] = col[v] ^ 1;
				que.push(u);
			}
			if (col[u] == col[v]) {
				std::cout << "impossible" << '\n';
				return 0;
			}
		}
	}

	std::cout << "possible" << '\n';

	return 0;
}

