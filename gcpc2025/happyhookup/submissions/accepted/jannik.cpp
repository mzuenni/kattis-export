#include <iostream>
#include <vector>

using namespace std;

int main()
{
	int n, m;
	cin >> n >> m;
	vector<vector<int>> g(n);
	while (m-- > 0) {
		int x, y;
		cin >> x >> y;
		g[x - 1].emplace_back(y - 1);
	}
	vector<bool> vis(n);
	const auto dfs = [&](auto&& self, int i) {
		if (vis[i])
			return;
		vis[i] = true;
		for (int j : g[i])
			self(self, j);
	};
	int a, b;
	cin >> a >> b;
	dfs(dfs, a - 1);
	auto va = vis;
	vis.assign(n, false);
	dfs(dfs, b - 1);
	for (int i = 0; i < n; i++)
		if (vis[i] and va[i]) {
			cout << "yes\n" << i+1 << endl;
			return 0;
		}
	cout << "no\n";
}
