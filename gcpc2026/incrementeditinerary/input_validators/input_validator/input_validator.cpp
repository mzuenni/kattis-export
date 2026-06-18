#include <algorithm>
#include <set>
#include <utility>
#include <vector>

#include "validation.h"

const int MAXN = 100000;
const int MAXM = 200000;

struct DSU {
	std::vector<int> p;
	DSU(int n) : p(n, -1) {}
	int leader(int u) {
		return p[u] < 0 ? u : p[u] = leader(p[u]);
	}
	void unite(int u, int v) {
		u = leader(u);
		v = leader(v);
		if (u == v) return;
		if (p[u] > p[v]) std::swap(u, v);
		p[u] += p[v];
		p[v] = u;
	}
	bool connected(int u, int v) {
		return leader(u) == leader(v);
	}
};

int main(int argc, char *argv[]) {
	InputValidator v(argc, argv);
	const auto n = v.read_integer("n", 2, MAXN);
	v.space();
	const auto m = v.read_integer("m", 1, MAXM);
	v.newline();

	std::set<std::pair<unsigned, unsigned>> edges;
	DSU dsu(n + 1);
	for (auto i = 0u; i < m; ++i) {
		const auto e = v.read_integers("e", 2, 1, n);
		v.check(e[0] != e[1], "Loop edge");
		const auto [_it, inserted] = edges.insert(std::minmax(e[0], e[1]));
		v.check(inserted, "Duplicate edge");
		dsu.unite(e[0], e[1]);
	}
	v.check(dsu.connected(1, n), "Missing path from 1 to n");
}
