#include <iostream>
#include <set>
#include <vector>
using namespace std;

void fail() {
	cout << "impossible" << '\n';
	exit(0);
}

struct bcc {
	int n, T = 0, top = -1;
	vector<pair<int,int>> edges;
	vector<int> t, st, perm;
	vector<vector<int>> adj;

	int other(int i, int e) {
		auto [a,b] = edges[e];
		return i^a^b;
	}

	// Given a cut vertex r and a list v of edge labels, find the vertices in
	// the biconnected component and then check whether the tiles form an even
	// permutation on the component.
	void process_block(int r, vector<int> v) {
		set<int> nodes;
		for (int e: v) {
			auto [a,b] = edges[e];
			nodes.insert(a);
			nodes.insert(b);
		}
		nodes.erase(r);

		set<int> labels;
		for (int a: nodes) {
			labels.insert(perm[a]);
		}
		// Is the component closed under the permutation?
		if (nodes != labels) fail();
	
		// Compute the parity of the permutation by counting the number of
		// swaps across all cycles.
		bool even = true;
		while (!nodes.empty()) {
			int a = *begin(nodes);
			even = !even;
			while (nodes.count(a)) {
				nodes.erase(a);
				a = perm[a];
				even = !even;
			}
		}
		if (!even) fail();
	}

	// Hopcroft/Tarjan's algorithm for computing the block-cut tree.
	int dfs(int i, int p) {
		int tmin = t[i] = T++;
		for (int e: adj[i]) if (e != p) {
			int j = other(i,e);
			if (t[j] >= 0) {
				tmin = min(tmin,t[j]);
				if (t[j] < t[i]) st.push_back(e);
			} else {
				int m = size(st), ntmin = dfs(j,e);
				tmin = min(tmin, ntmin);
				if (ntmin == t[i]) {
					st.push_back(e);
					process_block(i, vector<int>(begin(st)+m, end(st)));
					st.resize(m);
				} else if (ntmin < t[i]) st.push_back(e);
				else process_block(i, {e});
			}
		}
		return tmin;
	}
	
	bcc(int n, vector<pair<int,int>> edges, vector<int> perm):
			n(n), edges(edges), t(n,-1), perm(perm), adj(n) {
		for (int i = 0; i < ssize(edges); i++) {
			auto [a,b] = edges[i];
			adj[a].push_back(i);
			adj[b].push_back(i);
		}
		for (int i = 0; i < n; i++) {
			if (t[i] < 0) dfs(i,-1);
		}
	}
};

int main() {
	int h, w;
	cin >> h >> w;

	vector<string> blocked(h);
	for (string &s: blocked) cin >> s;

	vector<vector<int>> a(h, vector<int>(w));
	for (auto &v: a) for (int &x: v) cin >> x;

	auto id = [&](int i, int j) { return (i*w+j+1) % (h*w); };

	// Create a list of edges and compute the underlying permutation of the tiles.
	vector<int> perm(h*w);
	vector<pair<int,int>> edges;
	for (int i = 0; i < h; i++) {
		for (int j = 0; j < w; j++) {
			perm[id(i,j)] = a[i][j];
			if (blocked[i][j] == '#') continue;
			if (i+1 < h && blocked[i+1][j] == '.') {
				edges.emplace_back(id(i,j), id(i+1,j));
			}
			if (j+1 < w && blocked[i][j+1] == '.') {
				edges.emplace_back(id(i,j), id(i,j+1));
			}
		}
	}

	bcc B(h*w, edges, perm);
	cout << "possible" << '\n';
}
