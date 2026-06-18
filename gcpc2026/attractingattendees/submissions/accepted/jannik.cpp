#include <algorithm>
#include <cassert>
#include <iostream>
#include <vector>

using namespace std;

using pii = pair<int, int>;

int main()
{
	int n, m, c;
	cin >> n >> m >> c;

	// [0..m) are people, [m..m+n) are bands
	vector<vector<int>> g(n + m);
	vector<int> degree(n + m);
	vector<int> min_degree(n + m, c);
	for (int i = 0; i < m; i++) {
		cin >> degree[i];
		g[i].resize(degree[i]);
		min_degree[i] = (degree[i] + 1) / 2;
		for (int& x : g[i]) {
			cin >> x;
			x += m - 1;
			g[x].emplace_back(i), degree[x]++;
		}
	}

	vector<bool> attends(n + m, true);
	const auto remove = [&](auto&& self, int i) -> void {
		attends[i] = false;
		for (int j : g[i])
			if (attends[j] and --degree[j] < min_degree[j])
				self(self, j);
	};
	for (int i = 0; i < n + m; i++)
		if (attends[i] and degree[i] < min_degree[i])
			remove(remove, i);

	if (int k = count(attends.begin() + m, attends.end(), true)) {
		cout << "possible\n"
			 << k << '\n';
		for (int i = 0; i < n; i++)
			if (attends[i + m])
				cout << ' ' << i + 1;
		cout << endl;
	} else
		cout << "impossible\n";
}
