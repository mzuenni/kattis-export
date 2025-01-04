#include <iostream>
#include <vector>
#include <functional>

using namespace std;

int main() {
	int n, m;
	cin >> n >> m;

	vector<vector<int>> p(n);

	for(int i = 0; i < m; ++i) {
		int x, y; cin >> x >> y; x--, y--;
		p[x].push_back(y);
		p[y].push_back(x);
	}

	int res = 0;
	vector<bool> visited(n, false);

	function<int(int)> visit = [&](int i) {
		visited[i] = true;
		int k = 1;
		for (int j : p[i]) {
			if(!visited[j])
				k += visit(j);
		}

		return k;
	};

	for(int i = 0; i < n; ++i) {
		if (!visited[i])
			res = max(res, visit(i));
	}

	cout << res << endl;
}
