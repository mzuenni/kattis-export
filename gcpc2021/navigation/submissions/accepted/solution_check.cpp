// Author: Gregor Matl
// Runtime: O(s * log(s)) where s = sum over all k_i.

#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

// Number of vertices
#define MAX_N 1000000

// num vertices, num edges, num colors
int n, m, k; 

// color_index[u][c] = what index cindex has color c among the colors visible from intersection u?
map<int, int> color_index[MAX_N];

// outdegrees_by_color[u][cindex] = how many edges go out from intersection u and have color (by index) cindex?
vector<int> outdegrees_by_color[MAX_N];

// backedges[u] = list of edges ending at intersection u, containing origin intersection, edge color, length
vector<tuple<int, int, int> > backedges[MAX_N];

// dist_by_color[u][cindex] = what's the max dist we can end up with when picking color cindex at intersection u?
vector<ll> dist_by_color[MAX_N];

// dist_by_color[u] = what's the worst-case dist we can end up starting at intersection u when making the best possible pick?
ll dist[MAX_N];

// intermediate values
int u, v, t, l, c, cindex;

set<pair<int, int> > edges;

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);
	
	// input
	cin >> n >> m >> k;
	
	// some checks
	assert(n >= 1 && n <= 500000);
	assert(m >= 1 && m <= 500000);
	assert(k >= 1 && k <= 1000);

	int sumedges = 0;

	for (int i = 0; i < m; ++i) {
		cin >> u >> v >> t >> l;

		// some checks
		assert(u >= 1 && u <= n);
		assert(v >= 1 && v <= n);
		assert(t >= 1 && t <= 1000000);
		assert(l >= 1 && l <= k);
//		assert(edges.find(make_pair(u,v)) == edges.end());
		
		edges.insert(make_pair(u,v));
		u--;
		v--;
		
		set<int> diffcols;
		for (int j = 0; j < l; ++j) {
			cin >> c;
			// some checks
			assert(c >= 1 && c <= k);
			assert(diffcols.find(c) == diffcols.end());
			diffcols.insert(c);
			sumedges++;
		
			// edge from u to v with lenght t and color c
		
			// first check if color c has already appeared at intersection u, otherwise assign new index
			if (color_index[u].find(c) == color_index[u].end()) {
				color_index[u][c] = outdegrees_by_color[u].size();
				outdegrees_by_color[u].push_back(0);
			}
			
			// increase outdegree of edges of this color at intersection u
			outdegrees_by_color[u][color_index[u][c]]++;
			// enter edge to v as backedge
			backedges[v].push_back(make_tuple(u, color_index[u][c], t));
			
		}
	}
	
	// some checks
	assert(sumedges <= 500000);
		
	// modified backwards dijkstra
	priority_queue<pair<ll, int>, vector<pair<ll, int> >, greater<pair<ll, int>>> pq;

	for (int i = 0; i < n; ++i) {
		dist[i] = 1e18;
		dist_by_color[i] = vector<ll>(outdegrees_by_color[i].size(), 0);
	}
	
	// starting from the target...
	pq.push(make_pair(0, n - 1));
	dist[n-1] = 0;

	while(!pq.empty()) {
		// pick intersection v with minimum distance
		ll time = pq.top().first;
		v = pq.top().second;
		pq.pop();
		if (time > dist[v])
			continue; // we've treated this already

		for (auto backedge : backedges[v]) {
			// edge from u to v with length t and color cindex
			u = get<0>(backedge);
			cindex = get<1>(backedge);
			t = get<2>(backedge);
			
			// we might end up taking this path when showing color cindex at u, so we have to update our worst case
			if (time + t > dist_by_color[u][cindex]) {
				dist_by_color[u][cindex] = time + t;
			}
			outdegrees_by_color[u][cindex]--;
			
			// if we've processed all outcomes at u for color cindex, we could go on to process u as a whole.
			if (outdegrees_by_color[u][cindex] == 0) {
				if (dist_by_color[u][cindex] < dist[u]) {
					dist[u] = dist_by_color[u][cindex];
					pq.push(make_pair(dist[u], u));
				}
			}
		}
	}
	
	// output
	if (dist[0] == 1e18) {
		cout << "impossible" << endl;
	} else {
		cout << dist[0] << endl;
	}
}
