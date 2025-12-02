#include <bits/stdc++.h>
using namespace std;

#define all(x) begin(x), end(x)
#define sz(x) (ll)(x).size()

using ll = long long;
using ld = long double;

// unions[i] >= 0 => unions[i] =  parent
// unions[i]  < 0 => unions[i] = -height
vector<int> unions;

void init(int n) { //Initialisieren
	unions.assign(n, -1);
}

int findSet(int n) { // Pfadkompression
	if (unions[n] < 0) return n;
	return unions[n] = findSet(unions[n]);
}

void linkSets(int a, int b) { // Union by rank.
	if (unions[b] > unions[a]) swap(a, b);
	if (unions[b] == unions[a]) unions[b]--;
	unions[a] = b;
}

void unionSets(int a, int b) { // Diese Funktion aufrufen.
	if (findSet(a) != findSet(b)) linkSets(findSet(a), findSet(b));
}

struct edge {
	ll w, a, b;
	bool operator<(const edge& o) const {
		return w < o.w;
	}
};
vector<vector<pair<ll, ll>>> adj;
vector<ll> state;

ll dfs_cycles(ll cur, ll pref = -1, ll inW = 0) {
	ll res = 0;
	for (auto [x, w] : adj[cur]) {
		if (x == pref) continue;
		res += dfs_cycles(x, cur, w);
		state[cur] ^= state[x];
	}
	if (state[cur] != 0 && pref >= 0) {
		res += inW;
		unionSets(cur, pref);
	}
	return res;
}

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);
	ll n;
	cin >> n;
	adj.assign(n, {});
	vector<edge> edges(n-1);
	for (auto& [w, a, b] : edges) {
		cin >> a >> b >> w;
		a--;
		b--;
		adj[a].push_back({b, w});
		adj[b].push_back({a, w});
	}
	ll m;
	cin >> m;
	state.assign(n, 0);
	vector<edge> bridges(m);
	ll root = -1;
	for (auto& [_, a, b] : bridges) {
		cin >> a >> b;
		a--;
		b--;
		state[a] ^= 1;
		state[b] ^= 1;
		root = a;
	}

	init(n);
	ll res = dfs_cycles(root);

	//contract bridges on cycles
	for (auto [_, a, b] : bridges) {
		unionSets(a, b);
	}

	//check connectivity
	root = findSet(root);
	bool possible = true;
	for (auto& [w, a, b] : bridges) {
		possible &= findSet(a) == root;
	}

	if (!possible) {
		cout << "impossible" << endl;
	} else {
		cout << res << endl;
	}
}
