#include <algorithm>
#include <iostream>
#include <numeric>
#include <vector>

using namespace std;

#define all(a) (a).begin(), (a).end()

int main()
{
	int n, k;
	cin >> n >> k;
	vector<int> pa(n, -1), depth(n, 0);
	vector<vector<int>> children(n);
	for (int i = 1; i < n; i++) {
		cin >> pa[i];
		depth[i] = depth[--pa[i]] + 1;
		children[pa[i]].emplace_back(i);
	}

	vector<int> order(n);
	iota(all(order), 0);
	sort(all(order), [&](int i, int j) { return depth[i] > depth[j]; });
	vector<bool> covered(n);
	vector<int> sampled;
	for (int i : order) {
		if (covered[i])
			continue;
		int pos = i;
		for (int j = 0; j < k and pos != 0; j++)
			pos = pa[pos];
		sampled.emplace_back(pos);
		const auto dfs = [&](auto&& self, int i, int k) -> void {
			if (k < 0 or covered[i])
				return;
			covered[i] = true;
			for (int j : children[i])
				self(self, j, k - 1);
		};
		dfs(dfs, pos, k);
	}
	cout << sampled.size() << endl;
	for (size_t i = 0; i < sampled.size(); i++)
		cout << sampled[i] + 1 << (i + 1 < sampled.size() ? ' ' : '\n');
}
