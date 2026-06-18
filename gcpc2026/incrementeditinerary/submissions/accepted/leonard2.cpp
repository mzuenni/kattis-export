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

	std::vector dist(n, std::vector<int>(2, -1));
	std::queue<std::pair<int, int>> que;

	dist[0][0] = 0;
	que.emplace(0, 0);

	while (!que.empty()) {
		auto [v, i] = que.front();
		que.pop();
		for (int u : graph[v]) {
			if (dist[u][0] == -1) {
				dist[u][0] = dist[v][i] + 1;
				que.emplace(u, 0);
			}
			else if (dist[u][1] == -1 && dist[v][i] == dist[u][0]) {
				dist[u][1] = dist[v][i] + 1;
				que.emplace(u, 1);
			}
		}
	}

	if (dist[n - 1][1] == -1) std::cout << "im";
	std::cout << "possible" << '\n';

	return 0;
}

