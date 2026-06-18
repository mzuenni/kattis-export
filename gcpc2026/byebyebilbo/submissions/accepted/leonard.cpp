#include <iostream>
#include <vector>

int main() {
	int n, k;
	std::cin >> n >> k;

	std::vector<std::vector<int>> tree(n + 1);

	for (int i = 2; i <= n; ++i) {
		int p;
		std::cin >> p;
		tree[p].push_back(i);
	}

	std::vector<int> ans;

	auto dfs = [&](auto&& self, int v) -> int {
		int maxDown = 0;
		for (int u : tree[v]) {
			maxDown = std::max(maxDown, self(self, u) + 1);
		}
		if (maxDown >= k - 1) {
			ans.push_back(v);
			maxDown = -1;
		}
		return maxDown;
	};

	if (dfs(dfs, 1) != -1) {
		ans.push_back(1);
	}

	std::cout << ans.size() << '\n';

	for (int v : ans) {
		std::cout << v << ' ';
	}

	std::cout << '\n';

	return 0;
}

