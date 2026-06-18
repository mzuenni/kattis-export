#include <iostream>
#include <vector>

using namespace std;

int main()
{
	int n, m;
	cin >> n >> m;
	vector<vector<int>> g(n);
	while (m-- > 0) {
		int a, b;
		cin >> a >> b;
		a--, b--;
		g[a].emplace_back(b), g[b].emplace_back(a);
	}

	const auto bfs = [&](int i) {
		vector<int> d(n, n + 10), q;
		q.emplace_back(i), d[i] = 0;
		for (int k = 0; k < (int)q.size(); k++) {
			for (int j : g[i = q[k]])
				if (d[j] > d[i] + 1)
					q.emplace_back(j), d[j] = d[i] + 1;
		}
		return d;
	};
	auto d0 = bfs(0), dn = bfs(n - 1);
	for (int i = 0; i < n; i++)
		for (int j : g[i])
			if (d0[i] + 1 + dn[j] == 1 + dn[0]) {
				cout << "possible\n";
				return 0;
			}
	cout << "impossible\n";
}
