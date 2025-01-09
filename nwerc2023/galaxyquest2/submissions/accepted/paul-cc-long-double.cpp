#include <cmath>
#include <iomanip>
#include <iostream>
#include <set>
#include <vector>
using namespace std;
using dbl = long double;

dbl f(dbl x) {
	return 1 - sqrtl(1-x);
}

void solve(dbl t, dbl s) {
	dbl c = t/s;
	if (c < 2) {
		cout << "impossible" << '\n';
	} else {
		dbl b = c*c - 2;
		dbl u = 0.5 * b * f(4/(b*b));
		dbl res = 2*s * sqrtl(u);
		cerr << fixed << setprecision(20) << u << '\n';
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

	vector<vector<pair<int,dbl>>> adj(n);
	while (m--) {
		int a, b;
		cin >> a >> b;
		a--, b--;
		dbl d = sqrtl(hypotl(x[b]-x[a], hypotl(y[b]-y[a], z[b]-z[a])));
		adj[a].emplace_back(b, d);
		adj[b].emplace_back(a, d);
	}

	vector<dbl> dist(n, 1e100);
	set<pair<dbl,int>> pq;

	auto consider = [&](int i, dbl d) {
		if (d > dist[i]) return;
		pq.erase({dist[i], i});
		dist[i] = d;
		pq.insert({dist[i], i});
	};

	consider(0, 0);
	while (!pq.empty()) {
		int i = begin(pq)->second;
		pq.erase(begin(pq));
		for (auto [j,d]: adj[i]) {
			consider(j, dist[i] + d);
		}
	}

	while (q--) {
		int a, t;
		cin >> a >> t;
		a--;
		solve(t, dist[a]);
	}
}
