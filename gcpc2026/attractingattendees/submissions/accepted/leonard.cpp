#include <iostream>
#include <queue>
#include <vector>

int main() {
	int n, m, c;
	std::cin >> n >> m >> c;

	std::vector<std::vector<int>> graph(n + m);
	std::vector<int> deg(n + m, 0), need(n + m, c);

	for (int i = n; i < n + m; ++i) {
		int k;
		std::cin >> k;
		need[i] = (k + 1) / 2;
		while (k--) {
			int j;
			std::cin >> j;
			j -= 1;
			graph[i].push_back(j);
			graph[j].push_back(i);
			deg[i] += 1;
			deg[j] += 1;
		}
	}

	std::queue<int> invalid;

	for (int i = 0; i < n; ++i) {
		if (deg[i] < need[i]) {
			invalid.push(i);
		}
	}

	while (!invalid.empty()) {
		int i = invalid.front();
		invalid.pop();
		for (int j : graph[i]) {
			deg[j] -= 1;
			if (deg[j] == need[j] - 1) {
				invalid.push(j);
			}
		}
	}

	std::vector<int> lineup;

	for (int i = 0; i < n; ++i) {
		if (deg[i] >= need[i]) {
			lineup.push_back(i);
		}
	}

	if (lineup.empty()) {
		std::cout << "impossible" << '\n';
	}
	else {
		std::cout << "possible" << '\n';
		std::cout << lineup.size() << std::endl;
		for (int i : lineup) {
			std::cout << i + 1;
			if (i != lineup.back()) std::cout << " ";
		}
		std::cout << '\n';
	}

	return 0;
}
