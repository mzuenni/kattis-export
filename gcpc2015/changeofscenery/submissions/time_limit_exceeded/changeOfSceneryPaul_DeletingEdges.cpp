#include <bits/stdc++.h>
using namespace std;

typedef pair<int,int> pii;
const int oo = 0x3f3f3f3f;
#define all(c) begin(c), end(c)

/*
	Delete path edges one by one and run Dijkstra on the remaining graph.
	Complexity: O(k*m*log(n)) 
*/

const int maxN = 10010;
vector<pii> adj[maxN];
int dist[maxN], path[maxN];
int n;

int dijkstra() {
	memset(dist,0x3f,n*sizeof(int));
	priority_queue<pii,vector<pii>,greater<pii>> q;
	dist[0] = 0;
	q.emplace(0,0);

	while (!q.empty()) {
		int d, i;
		tie(d,i) = q.top();
		q.pop();
		if (i == n-1) return d;
		if (d > dist[i]) continue;
		for (const auto &e: adj[i]) {
			int j, len;
			tie(j,len) = e;
			if (d + len >= dist[j]) continue;
			dist[j] = d + len;
			q.emplace(dist[j],j);
		}
	}
	return oo;
}

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	
	int m, k; cin >> n >> m >> k;
	
	for (int i = 0; i < k; i++) cin >> path[i], --path[i];
	
	for (int i = 0; i < m; i++) {
		int a, b, c; cin >> a >> b >> c;
		--a, --b;
		adj[a].emplace_back(b,c);
		adj[b].emplace_back(a,c);
	}

	for (int i = 0; i < n; i++) sort(all(adj[i]));

	int len = dijkstra();

	for (int i = 0; i+1 < k; i++) {
		auto it = lower_bound(all(adj[path[i]]),pii(path[i+1],0));
		int tmp = it->second;
		it->second = oo; // "delete" edge by setting its length to infinity
		if (dijkstra() == len) {
			cout << "YES" << endl;
			return 0;
		}
		it->second = tmp; // restore original length
	}

	cout << "NO" << endl;

}

