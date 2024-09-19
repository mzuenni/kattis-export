#include <bits/stdc++.h>
using namespace std;

int main() {
	ios::sync_with_stdio(false);
	cin.tie(0);

	int n, m;
	cin >> n >> m;
	vector<vector<pair<int, int>>> verb(n - 1);
	for (int i = 0; i < m; i++) {
		int j, d, t;
		cin >> j >> d >> t;
		j--;
		verb[j].emplace_back(d, t);
	}
	int q;
	cin >> q;
	for (int i = 0; i < q; i++) {
		int g;
		cin >> g;
		bool poss = true;
		int res = 0;
		for (long long j = 0; j < n - 1; j++) {
			int mi = 1e9;
			for (auto [d, t]: verb[j]) {
				if (t >= g) mi = min(mi, d);
			}
			if (mi == 1e9) {
				poss = false;
				cout << "impossible" << endl;
				break;
			} else {
				res += mi;
			}
		}
		if (poss) cout << res << endl;
	}
}
