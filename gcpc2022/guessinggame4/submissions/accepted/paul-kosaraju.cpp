#include <bits/stdc++.h>
using namespace std;

int main() {
	int n; cin >> n;

	array<int,7> g;
	for (int &x: g) cin >> x;

	array<int,8> s = {};
	partial_sum(begin(g), end(g), begin(s)+1);

	int m = 2*s[7];

	vector<vector<int>> picks(n+1, vector<int>(7));
	picks[n].resize(2);
	for (auto &v: picks) {
		int k = size(v);
		for (int i = 0; i < k; i++) {
			int a; cin >> a;
			v[i] = 2*(s[7-k+i] + abs(a) - 1) + (a < 0);
		}
	}
	
	auto dfs = [&](auto &adj, auto &mark, auto &order, int a) {
		auto rec = [&](const auto &self, int a) -> void {
			mark[a] = true;
			for (int b: adj[a]) {
				if (!mark[b]) self(self, b);
			}
			order.push_back(a);
		};
		rec(rec, a);
	};

	vector<vector<int>> adj(m), radj(m);
	
	auto add_edge = [&](int a, int b) {
		adj[a].push_back(b), radj[b].push_back(a);
	};

	for (int i = 0; i < n; i++) {
		for (int a: picks[i]) for (int b: picks[i]) if (a != b) {
			add_edge(a, b^1);
		}
	}
	for (int a: picks[n]) {
		add_edge(a^1, a);
	}

	vector<bool> mark(m);
	vector<int> order;
	for (int a = 0; a < m; a++) {
		if (!mark[a]) dfs(adj, mark, order, a);
	}
	reverse(begin(order), end(order));

	bool res = true;
	vector<int> comp(m, -1);
	mark = vector<bool>(m);
	for (int a: order) if (!mark[a]) {
        vector<int> cur;
        dfs(radj, mark, cur, a);
		for (int b: cur) {
			comp[b] = a;
			if (comp[b^1] == a) res = false;
		}
	}

	cout << (res ? "possible" : "impossible") << '\n';
}
