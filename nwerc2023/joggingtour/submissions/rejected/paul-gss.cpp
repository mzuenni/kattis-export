// @EXPECTED_RESULTS@: WRONG_ANSWER, TIME_LIMIT_EXCEEDED
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

double error(double a, double b) {
	return abs(b-a) / max(1.0, max(abs(a), abs(b)));
}

template<typename F>
double gss(double a, double b, F f) {
	double r = (sqrt(5)-1)/2;
	double x1 = b - r*(b-a), x2 = a + r*(b-a);
	double f1 = f(x1), f2 = f(x2);
	for (int z = 0; z < 80; z++) {
		if (error(x1, x2) < 1e-6 && error(f1, f2) < 1e-7) break;
		if (f1 < f2) {
			b = x2, x2 = x1, f2 = f1;
			x1 = b - r*(b-a), f1 = f(x1);
		} else {
			a = x1, x1 = x2, f1 = f2;
			x2 = a + r*(b-a), f2 = f(x2);
		}
	}
	return (f1+f2)/2;
}

int main() {
	int n; cin >> n;
	vector<int> x(n), y(n);
	for (int i = 0; i < n; i++) {
		cin >> x[i] >> y[i];
	}

	auto solve = [&](const double alpha) {
		double c = cos(alpha), s = sin(alpha);
		vector<vector<double>> dist(n, vector<double>(n));
		for (int a = 0; a < n; a++) {
			for (int b = 0; b < n; b++) {
				double dx = x[b]-x[a], dy = y[b]-y[a];
				dist[a][b] = abs(c*dx - s*dy) + abs(s*dx + c*dy);
			}
		}
		return tsp(dist);
	};

	vector<double> angles = {0, M_PI/2, M_PI, 3*M_PI/2};
	for (int i1 = 0; i1 < n; i1++) {
		for (int j1 = i1+1; j1 < n; j1++) {
			for (int i2 = 0; i2 < n; i2++) {
				for (int j2 = i2+1; j2 < n; j2++) {
					if (make_pair(i1, j1) <= make_pair(i2, j2)) continue;
					double dx1 = x[j1]-x[i1], dy1 = y[j1]-y[i1];
					double dx2 = x[j2]-x[i2], dy2 = y[j2]-y[i2];
					for (int mask = 0; mask < 16; mask++) {
						int s1 = (mask & 1) ? 1 : -1;
						int s2 = (mask & 2) ? 1 : -1;
						int s4 = (mask & 4) ? 1 : -1;
						int s8 = (mask & 8) ? 1 : -1;
						double u = s1*dx1 + s2*dy1 - s4*dx2 - s8*dy2;
						double v = s1*dy1 - s2*dx1 - s4*dy2 + s8*dx2;
						if (u == 0 && v == 0) continue;
						double alpha = atan(u/v);
						double c = cos(alpha), s = sin(alpha);
						double dist1 = abs(c*dx1 - s*dy1) + abs(s*dx1 + c*dy1);
						double dist2 = abs(c*dx2 - s*dy2) + abs(s*dx2 + c*dy2);
						if (abs(dist1-dist2) < 1e-6) angles.push_back(alpha);
					}
				}
			}
		}
	}
	sort(begin(angles), end(angles));
	angles.push_back(angles[0] + 2*M_PI);

	double res = 1e20;
	for (int i = 0; i+1 < angles.size(); i++) {
		double a = angles[i], b = angles[i+1];
		if (b-a < 1e-6) continue;
		res = min(res, gss(a, b, solve));
	}
	cout << fixed << setprecision(20) << res << '\n';
}
