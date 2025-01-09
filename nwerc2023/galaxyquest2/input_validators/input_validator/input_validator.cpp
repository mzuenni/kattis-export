#include "validation.h"
#include <set>
#include <tuple>
#include <vector>
using namespace std;

const long double oo = 1e30;

vector<long double> dijkstra(const vector<vector<pair<int, long double>>> &adj, int s) {
	int n = size(adj);
	vector<long double> dist(n, oo);
	set<pair<long double, int>> pq;

	auto consider = [&](int a, long double d) {
		if (dist[a] <= d) return;
		pq.erase({dist[a], a});
		dist[a] = d;
		pq.insert({dist[a], a});
	};

	consider(0, 0);
	while (!pq.empty()) {
		int a = begin(pq)->second;
		pq.erase(begin(pq));
		for (auto [b,d]: adj[a]) {
			consider(b, dist[a]+d);
		}
	}
	return dist;
}

bool distance_ok(long double a, long double b) {
	long double abs_dist = abs(a-b);
	long double rel_dist = abs(a-b) / min(a,b);
	return min(abs_dist, rel_dist) > 1.1e-6;
}

const int X = 1000;

int main(int argc, char *argv[]) {
    InputValidator v(argc, argv);

    int n = v.read_integer("n", 2, 100'000);
    v.space();
    int m = v.read_integer("m", 1, 100'000);
    v.space();
    int q = v.read_integer("q", 1, 100'000);
    v.newline();

	set<tuple<int,int,int>> points;

	vector<int> x(n), y(n), z(n);
	for (int i = 0; i < n; i++) {
		x[i] = v.read_integer("x", -X, X);
		v.space();
		y[i] = v.read_integer("y", -X, X);
		v.space();
		z[i] = v.read_integer("z", -X, X);
		v.newline();
		points.emplace(x[i], y[i], z[i]);
	}

	v.check(points.size() == n, "points are not unique");

	set<pair<int,int>> edges;

	vector<vector<pair<int, long double>>> adj(n);
	for (int i = 0; i < m; i++) {
		int a = v.read_integer("a", 1, n) - 1;
		v.space();
		int b = v.read_integer("b", 1, n) - 1;
		v.newline();
		v.check(a != b, "found a self loop");
		if (a > b) swap(a, b);
		edges.emplace(a, b);

		long double d = sqrtl(hypotl(x[b]-x[a], hypotl(y[b]-y[a], z[b]-z[a])));
		adj[a].emplace_back(b, d);
		adj[b].emplace_back(a, d);
	}

	v.check(edges.size() == m, "edges are not unique");

	auto dist = dijkstra(adj, 0);

	while (q--) {
		int c = v.read_integer("c", 2, n) - 1;
		v.space();
		int t = v.read_integer("t", 1, X);
		v.newline();

		v.check(distance_ok(2*dist[c], t), "value t too close to fastest possible time");
	}
}
