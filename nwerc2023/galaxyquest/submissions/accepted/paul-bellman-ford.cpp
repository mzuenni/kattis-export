#include <cmath>
#include <iomanip>
#include <iostream>
#include <set>
#include <vector>
using namespace std;

// Computes the value 1 - sqrt(1-x) while avoiding catastrophic cancellation.
// Uses the direct evaluation for large x and an alternative expression for large x.
double f(double x) {
	if (x > 0.5) {
		return 1 - sqrt(1-x);
	} else {
		return x / (1 + sqrt(1-x));
	}
}

void solve(double t, double s) {
	double c = t/s;
	if (c < 2) {
		cout << "impossible" << '\n';
	} else {
		double b = c*c - 2;
		double u = 0.5 * b * f(4/(b*b));
		double res = 2*s * sqrt(u);
		cout << fixed << setprecision(20) << res << '\n';
	}
}

int main() {
	int n, m, q;
	cin >> n >> m >> q;

	vector<int> x(n), y(n), z(n);
	for (int i = 0; i < n; i++) {
		cin >> x[i] >> y[i] >> z[i];
	}

	vector<vector<pair<int,double>>> adj(n);
	while (m--) {
		int a, b;
		cin >> a >> b;
		a--, b--;
		double d = sqrt(hypot(x[b]-x[a], hypot(y[b]-y[a], z[b]-z[a])));
		adj[a].emplace_back(b, d);
		adj[b].emplace_back(a, d);
	}

	// Bellman-Ford is fast enough here, because the low bounds in the coordinates
	// mean that any shortest path can be at most ~500 edges in length.
	vector<double> dist(n, 1e100);
	dist[0] = 0;
	for (int k = 0; k < 555; k++) {
		for (int i = 0; i < n; i++) {
			for (auto [j,d]: adj[i]) {
				dist[j] = min(dist[j], dist[i] + d);
			}
		}
	}

	while (q--) {
		int a, t;
		cin >> a >> t;
		a--;
		solve(t, dist[a]);
	}
}
