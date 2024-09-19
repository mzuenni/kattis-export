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

	while (true) {
		vector<string> res(m, string(n, '.'));
		int i = 0, j = 0;
		bool ok = true;
		for (int t = 0; t < k; t++) {
			if (!ok) break;

			while (res[i][j] != '.') {
				if (++j == n) j = 0, i++;
			}

			int s = rand() % size(shapes);
			auto [a,b] = shapes[s];
			
			if (i+a > m || j+b > n) {
				ok = false;
				break;
			}

			for (int ii = i; ii < i+a; ii++) {
				for (int jj = j; jj < j+b; jj++) {
					if (res[ii][jj] != '.') ok = false;
					res[ii][jj] = str[t];
				}
			}
		}
			
		if (ok) {
			for (string s: res) cout << s << '\n';
			break;
		}
	}
}
