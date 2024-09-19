#include <bits/stdc++.h>
using namespace std;

int main() {
	srand(987);

	int m, n, k;
	cin >> m >> n >> k;

	int c = m*n / k;
	if (k*c != m*n) {
		cout << "impossible" << '\n';
		return 0;
	}

	vector<pair<int,int>> shapes;
	for (int a = 1; a <= c; a++) {
		if (c%a == 0) shapes.emplace_back(a, c/a);
	}

	string str(k, ' ');
	iota(begin(str), end(str), 'A');
	random_shuffle(begin(str), end(str));

	vector<string> res(m, string(n, '.'));
	auto rec = [&](const auto &self, int i, int j, int depth) -> void {
		if (depth == k) {
			for (string s: res) cout << s << '\n';
			exit(0);
		}
		
		while (res[i][j] != '.') {
			if (++j == n) j = 0, i++;
		}

		vector<int> p(size(shapes));
		iota(begin(p), end(p), 0);
		random_shuffle(begin(p), end(p));

		for (int t: p) {
			auto [a,b] = shapes[t];
			if (i+a > m || j+b > n) continue;

			bool ok = true;
			for (int ii = i; ii < i+a; ii++) {
				for (int jj = j; jj < j+b; jj++) {
					if (res[ii][jj] != '.') ok = false;
				}
			}
			if (!ok) continue;
			
			for (int ii = i; ii < i+a; ii++) {
				for (int jj = j; jj < j+b; jj++) {
					res[ii][jj] = str[depth];
				}
			}

			self(self, i, j, depth+1);
			
			for (int ii = i; ii < i+a; ii++) {
				for (int jj = j; jj < j+b; jj++) {
					res[ii][jj] = '.';
				}
			}
		}
	};

	rec(rec, 0, 0, 0);
	cout << "impossible" << '\n';
}
