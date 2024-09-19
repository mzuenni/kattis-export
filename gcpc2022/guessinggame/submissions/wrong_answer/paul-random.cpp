#include <bits/stdc++.h>
using namespace std;

int main() {
	clock_t start = clock();

	int n; cin >> n;

	array<int,7> g;
	for (int &x: g) cin >> x;

	vector<vector<int>> picks(n+1, vector<int>(7));
	picks[n].resize(2);
	for (auto &v: picks) {
		for (int &x: v) cin >> x;
	}
	for (int i = 0; i < 5; i++) {
		picks[n].insert(begin(picks[n]), 0);
	}

	bool res = false;
	mt19937_64 gen(987);
	while (double(clock()-start)/CLOCKS_PER_SEC < 0.9) {
		vector<vector<int>> v(7);
		for (int d = 0; d < 7; d++) {
			v[d].resize(g[d]);
			for (int i = 0; i < g[d]; i += 64) {
				auto x = gen();
				for (int k = 0; k < 64 && i+k < g[d]; k++) {
					v[d][i+k] = (x >> k) & 1;
				}
			}
		}

		auto check = [&](int d, int j) {
			int x = picks[j][d];
			return v[d][abs(x)-1] == (x > 0);
		};

		auto flip = [&](int d, int j) {
			int x = picks[j][d];
			v[d][abs(x)-1] ^= 1;
		};

		if (!check(5,n)) flip(5,n);
		if (!check(6,n)) flip(6,n);

		bool ok = true;
		for (int i = 0; i < n; i++) {
			int count = 0;
			for (int d = 0; d < 7; d++) {
				count += check(d,i);
			}
			if (count >= 2) {
				ok = false;
				break;
			}
		}

		if (ok) {
			res = true;
			break;
		}
	}

	cout << (res ? "possible" : "impossible") << '\n';
}
