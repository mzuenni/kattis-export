#include <cmath>
#include <iomanip>
#include <iostream>
#include <set>
#include <vector>
using namespace std;

void solve(double t, double s) {
	double c = t/s;
	if (c < 2) {
		cout << "impossible" << '\n';
	} else {
		double lo = 0, hi = 1;
		for (int z = 0; z < 80; z++) {
			double md = (lo+hi)/2;
			(md + 1/md < c ? hi : lo) = md;
		}
		double res = 2*s*lo;
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

	vector<double> dist(n, 1e100);
	set<pair<double,int>> pq;

	auto consider = [&](int i, double d) {
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
