#include <bits/stdc++.h>
using namespace std;

int main() {
	int n; cin >> n;
	vector<int> x(n), y(n);
	for (int i = 0; i < n; i++) {
		cin >> x[i] >> y[i];
	}

	vector<int> p(n);
	iota(begin(p), end(p), 0);

	double precalc[n][n][n][n];
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			double c = x[i]-x[j], s = y[j]-y[i], len = hypot(c, s);
			c /= len, s /= len;
			for (int a = 0; a < n; a++) {
				for (int b = 0; b < n; b++) {
					double dx = x[b]-x[a], dy = y[b]-y[a];
					precalc[i][j][a][b] = abs(c*dx - s*dy) + abs(s*dx + c*dy);
				}
			}
		}
	}

	double res = 1e20;
	do {
		vector<pair<int,int>> v(n-1);
		vector<int> dx(n-1), dy(n-1);
		for (int i = 0; i < n-1; i++) {
			dx[i] = x[p[i+1]]-x[p[i]];
			dy[i] = y[p[i+1]]-y[p[i]];
		}
		for (int i = 0; i < n-1; i++) {
			double cur = 0;
			for (int j = 0; j < n-1; j++) {
				cur += precalc[p[i]][p[i+1]][p[j]][p[j+1]];
			}
			res = min(res, cur);
		}
	} while (next_permutation(begin(p), end(p)));
	cout << fixed << setprecision(20) << res << '\n';
}
