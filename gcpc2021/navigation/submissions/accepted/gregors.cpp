#include <iostream>
#include <map>
#include <vector>
#include <set>
#include <utility>
using namespace std;
using ll = long long;
const ll INF = 1e17;

struct Edge {int u, c, t;};

int main() {
	int n,m,k; cin >> n >> m >> k;
	vector<map<int,int>> deg(n);
	vector<ll> dist(n,INF);
	vector<vector<Edge>> g(n);
	for (int i = 0; i < m; ++i) {
		int u,v,t,l; cin >> u >> v >> t >> l;
		u--; v--;
		for (int j = 0; j < l; ++j) {
			int c; cin >> c;
			deg[u][c]++;
			g[v].push_back({u,c,t});
		}
	}
	vector<map<int,ll>> colDist(n);
	set<pair<ll,int>> pq;
	pq.insert({0,n-1});
	while (!pq.empty()) {
		ll d = pq.begin()->first;
		int v = pq.begin()->second;
		pq.erase(pq.begin());
		if (d > dist[v]) continue;
		for (Edge &e : g[v]) {
			int c = e.c; int u = e.u; int t = e.t;
			colDist[u][c] = max(colDist[u][c], d+t);
			if (--deg[u][c] == 0 && colDist[u][c] < dist[u]) {
				dist[u] = colDist[u][e.c];
				pq.emplace(dist[u],u);
			}
		}
	}
	if (dist[0] == INF) cout << "impossible" << endl;
	else cout << dist[0] << endl;
}
