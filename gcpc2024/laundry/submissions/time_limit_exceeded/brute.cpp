#include <bits/stdc++.h>
using namespace std;

#define all(x) begin(x), end(x)
#define sz(x) (ll)(x).size()

using ll = long long;
using ld = long double;

struct edge {
	int from, to;
	ll f, c;
};

vector<edge> edges;
vector<vector<int>> adj;
int s, t, dfsCounter;
vector<int> visited;
ll capacity;

void addEdge(int from, int to, ll c) {
	adj[from].push_back(sz(edges));
	edges.push_back({from, to, 0, c});
	adj[to].push_back(sz(edges));
	edges.push_back({to, from, 0, 0});
}

bool dfs(int v) {
	if (v == t) return true;
	if (visited[v] == dfsCounter) return false;
	visited[v] = dfsCounter;
	for (int id : adj[v]) {
		if (edges[id].c >= capacity && dfs(edges[id].to)) {
			edges[id].c -= capacity; edges[id ^ 1].c += capacity;
			edges[id].f += capacity; edges[id ^ 1].f -= capacity;
			return true;
	}}
	return false;
}

ll maxFlow(int source, int target) {
	capacity = 1ll << 62;
	s = source;
	t = target;
	ll flow = 0;
	visited.assign(sz(adj), 0);
	dfsCounter = 0;
	while (capacity) {
		while (dfsCounter++, dfs(s)) flow += capacity;
		capacity /= 2;
	}
	return flow;
}

void solve() {
	ll k;
	cin >> k;
	vector<ll> in(8);
	cin >> in[1] >> in[2] >> in[4] >> in[3] >> in[6] >> in[5] >> in[7];
	ll sum = 0;
	for (ll x : in) sum += x;
	for (ll total = sum / k;; total++) {
		for (ll a = in[1] / k; a <= total; a++) {
			for (ll b = in[2] / k; a+b <= total; b++) {
				ll c = total - a - b;
				edges.clear();
				adj.assign(9, {});
				for (ll i = 1; i < 8; i++) addEdge(0, i, in[i]);
				addEdge(1, 8, a*k);
				addEdge(2, 8, b*k);
				addEdge(4, 8, c*k);
				addEdge(7, 1, in[7]);
				addEdge(7, 2, in[7]);
				addEdge(7, 4, in[7]);
				addEdge(3, 1, in[3]);
				addEdge(5, 1, in[5]);
				addEdge(3, 2, in[3]);
				addEdge(6, 2, in[6]);
				addEdge(5, 4, in[5]);
				addEdge(6, 4, in[6]);
				if (maxFlow(0, 8) == sum) {
					cout << total << endl;
					return;
				}
			}
		}
	}
}

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);

	ll t; 
	cin >> t; 
	while (t--) solve(); 
}
