// check if vertex n can be reached by a path whose length has
// a different parity than the shortest path

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

	std::vector visited(n, std::vector<bool>(2, false));
	std::queue<std::pair<int, int>> que;

	visited[0][0] = true;
	que.emplace(0, 0);

	while (!que.empty()) {
		auto [v, i] = que.front();
		que.pop();
		for (int u : graph[v]) {
			if (!visited[u][i ^ 1]) {
				visited[u][i ^ 1] = true;
				que.emplace(u, i ^ 1);
			}
		}
	}

	if (!visited[n - 1][1]) std::cout << "im";
	std::cout << "possible" << '\n';

	return 0;
}

