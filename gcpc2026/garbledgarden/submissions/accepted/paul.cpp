#include <bits/stdc++.h>
using namespace std;

struct euler_path {
	int n;
	vector<vector<int>> adj;
	vector<int> pos, indeg, path;

	euler_path(vector<vector<int>> adj): n(adj.size()), adj(adj), pos(n), indeg(n) {
        for (int i = 0; i < n; i++) {
            for (int j: adj[i]) indeg[j]++;
        }
	}
	
	void rec(int i) {
		while (pos[i] < int(adj[i].size())) rec(adj[i][ pos[i]++ ]);
		path.push_back(i);
	}

	bool construct() {
		int s = -1, t = -1;
		for (int i = 0; i < n; i++) {
			int in = indeg[i], out = adj[i].size();
			if (abs(in-out) > 1) return false;
			if (in < out) { if (s < 0) s = i; else return false; }
			if (in > out) { if (t < 0) t = i; else return false; }
		}
		if ((s < 0) != (t < 0)) return false;
		if (s < 0) for (int i = 0; i < n; i++) if (adj[i].size()) s = i;
		if (s < 0) return true;
		rec(s);
		reverse(begin(path), end(path));
		return int(path.size()) == accumulate(begin(indeg), end(indeg), 0) + 1;
	}
};

vector<vector<int>> solve() {
    int n; cin >> n;
    vector<int> a(n);
    for (int &x: a) cin >> x, x--;
    vector<int> b = a;
    sort(begin(b), end(b));

    if (a == b) return {};

    vector<vector<int>> adj(n);
    map<pair<int,int>, vector<int>> indices;
    for (int i = 0; i < n; i++) {
        if (a[i] == b[i]) continue;
        adj[a[i]].push_back(b[i]);
        indices[make_pair(a[i], b[i])].push_back(i);
    }

    euler_path E(adj);
    if (E.construct()) {
        vector<int> res;
        for (int i = 0; i+1 < int(E.path.size()); i++) {
            auto p = make_pair(E.path[i], E.path[i+1]);
            res.push_back(indices[p].back());
            indices[p].pop_back();
        }
        return {res};
    }

    vector<pair<int,int>> c(n);
    for (int i = 0; i < n; i++) {
        c[i] = {a[i], i};
    }
    sort(begin(c), end(c));

    vector<int> mark(n);
    vector<vector<int>> res(2);
    for (int i = 0; i < n; i++) if (!mark[i]) {
        for (; !mark[i]; i = c[i].second) {
            res[0].push_back(i), mark[i] = 1;
        }
        res[1].push_back(res[0].back());
    }
    reverse(begin(res[1]), end(res[1]));
    return res;
}

int main() {
    auto res = solve();
    cout << res.size() << '\n';
    for (auto p: res) {
        cout << p.size() << '\n';
        for (int x: p) cout << x+1 << ' ';
        cout << '\n';
    }
}
