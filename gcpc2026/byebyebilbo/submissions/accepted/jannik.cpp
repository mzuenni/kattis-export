#include <iostream>
#include <vector>

using namespace std;

#define all(a) (a).begin(), (a).end()

int main()
{
	int n, k;
	cin >> n >> k;
	vector<vector<int>> children(n);
	for (int i = 1, pa; i < n; i++) {
		cin >> pa;
		children[pa - 1].emplace_back(i);
	}
	vector<int> res;
	const auto dfs = [&](auto&& self, int i) -> int {
		int d = 1;
		for (int c : children[i])
			d = max(d, 1 + self(self, c));
		if (d >= k or i == 0) {
			res.emplace_back(i + 1);
			d = 0;
		}
		return d;
	};
	dfs(dfs, 0);
	cout << res.size() << endl;
	for (size_t i = 0; i < res.size(); i++)
		cout << res[i] << (i + 1 < res.size() ? ' ' : '\n');
}
