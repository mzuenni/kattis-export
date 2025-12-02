#include "validate.h"

using namespace std;
#define all(x) ::begin(x), ::end(x)

// copied from yidi.cpp
int main(int argc, char **argv) {
	InputValidator::init(argc, argv);
	using namespace InputValidator;

	int n = testIn.integer();
	testIn.newline();
	vector<vector<pair<int, int>>> g(n);
	vector<vector<pair<int, int>>> g2(n);
	for (int i=1; i<n; i++) {
		int u = testIn.integer();
		testIn.space();
		int v = testIn.integer();
		testIn.space();
		int w = testIn.integer();
		testIn.newline();
		u--, v--;
		g[u].emplace_back(v, w);
		g[v].emplace_back(u, w);
	}
	
	int m = testIn.integer();
	testIn.newline();
	vector<int> a(n);
	vector<int> vis;
	int root = -1;
	for (int i=0; i<m; i++) {
		int u = testIn.integer();
		testIn.space();
		int v = testIn.integer();
		testIn.newline();
		u--, v--;
		a[u] ^= 1, a[v] ^= 1;
		g2[u].emplace_back(v, ssize(vis));
		g2[v].emplace_back(u, ssize(vis));
		vis.push_back(false);
		root = u;
	}
	
	auto dfs = [&](auto& self, int u, int p, int W) -> void {
		for (auto [v, w] : g[u]) if (v != p) {
				self(self, v, u, w);
				a[u] ^= a[v];
			}
		if (a[u]) {
			g2[u].emplace_back(p, ssize(vis));
			g2[p].emplace_back(u, ssize(vis));
			vis.push_back(false);
		}
	};
	dfs(dfs, 0, 0, 0);
	
	auto euler = [&](auto& self, int u) -> void {
		while (!g2[u].empty()) {
			auto [v, ind] = g2[u].back();
			g2[u].pop_back();
			if (vis[ind]) continue;
			vis[ind] = true;
			self(self, v);
		}
	};
	euler(euler, root);
	
	if (accumulate(all(vis), 0) != ssize(vis)) {
		juryOut << "impossible" << WA;
	}
	else return AC;
}
