#include <cassert>
#include <iostream>
#include <queue>
#include <vector>
#include <chrono>

using ll = long long;
constexpr ll MAX_TIME = 1.8e9;

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

	std::vector<int> dist(n + 1, -1);
	std::queue<int> que;
	dist[1] = 0;
	que.push(1);
	
	while (!que.empty()) {
		int v = que.front();
		que.pop();
		for (int u : graph[v]) {
			if (dist[u] == -1) {
				dist[u] = dist[v] + 1;
				que.push(u);
			}
		}
	}

	assert(dist[n] != -1);

	std::vector<bool> visited(n + 1, false);

	ll start = std::chrono::high_resolution_clock().now().time_since_epoch().count();
	int steps = 0;

	auto dfs = [&](auto&& self, int v, int depth) -> bool {
		if(++steps % 100 == 0){
			ll now = std::chrono::high_resolution_clock().now().time_since_epoch().count();
			if(now - start > MAX_TIME){
				std::cout << "impossible\n";
				exit(0);
			}
		}
		if (v == n) {
			return depth == dist[n] + 1;
		}
		if (depth + 1 <= dist[n] + 1) {
			for (int u : graph[v]) {
				if (!visited[u]) {
					visited[u] = true;
					if (self(self, u, depth + 1)) {
						return true;
					}
					visited[u] = false;
				}
			}
		}
		return false;
	};

	visited[1] = true;
	std::cout << (dfs(dfs, 1, 0) ? "" : "im") << "possible" << '\n';

	return 0;
}