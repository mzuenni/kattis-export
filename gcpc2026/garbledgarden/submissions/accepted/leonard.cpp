#include <algorithm>
#include <iostream>
#include <map>
#include <vector>

struct DSU {
	std::vector<int> p;
	DSU(int n) : p(n, -1) {}
	int leader(int u) {
		return p[u] < 0 ? u : p[u] = leader(p[u]);
	}
	bool unite(int u, int v) {
		u = leader(u);
		v = leader(v);
		if (u == v) return false;
		if (p[u] > p[v]) std::swap(u, v);
		p[u] += p[v];
		p[v] = u;
		return true;
	}
};

int main() {
	int n;
	std::cin >> n;

	std::vector<int> a(n);

	for (int i = 0; i < n; ++i) {
		std::cin >> a[i];
	}

	std::vector<int> sorted = a;
	std::sort(sorted.begin(), sorted.end());

	if (a == sorted) {
		std::cout << 0 << '\n';
		return 0;
	}

	std::map<int, std::vector<int>> indices_a, indices_sorted;

	for (int i = 0; i < n; ++i) {
		indices_a[a[i]].push_back(i);
		indices_sorted[sorted[i]].push_back(i);
	}

	std::vector<int> p(n);
	DSU dsu(n);

	for (int i = 0; i < n; ++i) {
		p[i] = indices_sorted[a[i]].back();
		indices_sorted[a[i]].pop_back();
		dsu.unite(i, p[i]);
	}

	for (auto [val, indices] : indices_a) {
		for (int i = 1; i < (int) indices.size(); ++i) {
			if (dsu.unite(indices[0], indices[i])) {
				std::swap(p[indices[0]], p[indices[i]]);
			}
		}
	}

	std::vector<bool> allSame(n, true);

	for (int i = 0; i < n; ++i) {
		if (a[i] != a[p[i]]) {
			allSame[dsu.leader(i)] = false;
		}
	}

	int cntCyclesGreater1 = 0;

	for (int i = 0; i < n; ++i) {
		if (dsu.leader(i) == i && !allSame[i] && dsu.p[i] <= -2) {
			cntCyclesGreater1 += 1;
		}
	}

	auto op = [&](std::vector<int> cycle) {
		std::cout << cycle.size() << '\n';
		for (int i = cycle.size() - 2; i >= 0; --i) {
			std::swap(p[cycle[i]], p[cycle[i + 1]]);
			std::cout << cycle[i + 1] + 1 << ' ';
		}
		std::cout << cycle[0] + 1 << '\n';
	};

	if (cntCyclesGreater1 == 1) {
		std::cout << 1 << '\n';
	}
	else {
		std::cout << 2 << '\n';
		std::vector<int> cycle;
		for (int i = 0; i < n; ++i) {
			if (dsu.leader(i) == i) {
				cycle.push_back(i);
			}
		}
		op(cycle);
	}

	for (int i = 0; i < n; ++i) {
		if (dsu.leader(i) == i && !allSame[i] && dsu.p[i] <= -2) {
			std::vector<int> cycle = {i, p[i]};
			while (cycle.back() != cycle[0]) {
				cycle.push_back(p[cycle.back()]);
			}
			cycle.pop_back();
			op(cycle);
			break;
		}
	}

	return 0;
}

