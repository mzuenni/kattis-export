#include <bits/stdc++.h>
using namespace std;

struct dsu {
	int n;
	vector<int> p, s;

	dsu(int n): n(n), p(n), s(n, 1) {
		iota(begin(p), end(p), 0);
	}
	
	int find(int x) {
		if (x == p[x]) return x;
		return p[x] = find(p[x]);
	}

	bool unite(int x, int y) {
		x = find(x), y = find(y);
		if (x == y) return false;
		
		if (s[x] < s[y]) swap(x,y);
        s[x] += s[y];
		p[y] = x;
		return true;
	}
};

int main() {
    int n, m;
    cin >> n >> m;

    vector<array<int,3>> edges(m);
    for (auto &[t, a, b]: edges) {
        cin >> a >> b >> t, a--, b--;
    }
    sort(begin(edges), end(edges), greater());

    dsu D(n);

    vector<int> col(n);
    vector<vector<int>> adj(n);
    vector<int> sum;
    long res = 0;
    for (int i = 0; i < m;) {
        int j = i;
        set<int> nodes;
        for (; j < m && edges[j][0] == edges[i][0]; j++) {
            int a = D.find(edges[j][1]), b = D.find(edges[j][2]);
            adj[a].push_back(b);
            adj[b].push_back(a);
            col[a] = col[b] = -1;
            nodes.insert(a);
            nodes.insert(b);
        }
        bool ok = 1;
        auto dfs = [&](const auto &self, int a) -> void {
            sum[col[a]] += D.s[a];
            for (int b: adj[a]) {
                if (col[b] < 0) {
                    col[b] = 1-col[a];
                    self(self, b);
                }
                if (col[b] == col[a]) ok = 0;
            }
        };
        for (int a: nodes) if (col[a] < 0) {
            col[a] = 0;
            sum = {0, 0};
            dfs(dfs, a);
            res += min(sum[0], sum[1]);
        }
        if (!ok) {
            cout << "impossible" << '\n';
            exit(0);
        }
        for (; i < j; i++) {
            D.unite(edges[i][1], edges[i][2]);
        }
    }
    cout << "possible\n" << res << '\n';
}
