#include <bits/stdc++.h>
using namespace std;

void self_min(double &x, double y) {
	x = min(x, y);
}

double tsp(const vector<vector<double>> &dist) {
	int n = dist.size();
	vector<vector<double>> dp(1 << n, vector<double>(n, 1e20));
	for (int i = 0; i < n; i++) dp[1 << i][i] = 0;
	for (int mask = 0; mask < (1 << n); mask++) {
		for (int i = 0; i < n; i++) if (mask & (1 << i)) {
			for (int j = 0; j < n; j++) if (!(mask & (1 << j))) {
				self_min(dp[mask | (1 << j)][j], dp[mask][i] + dist[i][j]);
			}
		}
	}
	return *min_element(begin(dp.back()), end(dp.back()));
}

int main() {
	int n; cin >> n;
	vector<int> x(n), y(n);
	for (int i = 0; i < n; i++) {
		cin >> x[i] >> y[i];
	}

	double res = 1e20;
	for (int i = 0; i < n; i++) {
		for (int j = i+1; j < n; j++) {
			double alpha = -atan2(y[j]-y[i], x[j]-x[i]);
			double c = cos(alpha), s = sin(alpha);
			vector<vector<double>> dist(n, vector<double>(n));
			for (int a = 0; a < n; a++) {
				for (int b = 0; b < n; b++) {
					double dx = x[b]-x[a], dy = y[b]-y[a];
					dist[a][b] = abs(c*dx - s*dy) + abs(s*dx + c*dy);
				}
			}
			res = min(res, tsp(dist));
		}
	}
	cout << fixed << setprecision(20) << res << '\n';
}
