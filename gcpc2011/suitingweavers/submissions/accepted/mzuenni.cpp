#include <bits/stdc++.h>
using namespace std;

#define fora(i, n) for (int i = 0; i < n; ++i)
#define forb(i, n) for (int i = 1; i<= n; ++i)
#define forc(i, n) for (const auto &i : n)
#define mp make_pair
#define eb emplace_back
#define pb push_back
#define sz(x) (int)(x).size()

using ll = long long;
using ld = long double;
using vi = vector<int>;

constexpr long long INF = 0x3FFFFFFFFFFFFFFll;

struct edge {
	long long from;
	long long to;
	long long f;
	long long c;
};

vector<edge> edges;
vector<vector<long long>> adjList;

long long m, s, t;
vector<long long> pt, dist;
long long flow, lim;
queue<long long> q;

void addEdge(long long from, long long to, long long c) {
	adjList[from].push_back(edges.size());
	edges.push_back(edge{from, to, 0, c});
	adjList[to].push_back(edges.size());
	edges.push_back(edge{to, from, 0, 0});
}

bool bfs() {
	for (long long i = 0; i < adjList.size(); i++) dist[i] = INF;
	dist[s] = 0;
	q.push(s);
	while (!q.empty() && dist[t] == INF) {
		long long cur = q.front(); q.pop();
		for (long long i = 0; i < adjList[cur].size(); i++) {
			long long id = adjList[cur][i], to = edges[id].to;
			if (dist[to] == INF && edges[id].c - edges[id].f >= lim) {
				dist[to] = dist[cur] + 1;
				q.push(to);
			}
		}
	}
	while (!q.empty()) q.pop();
	return dist[t] != INF;
}

bool dfs(long long v, long long flow) {
	if (flow == 0) return false;
	if (v == t) return true;
	for (; pt[v] < (int)adjList[v].size(); pt[v]++) {
		long long id = adjList[v][pt[v]], to = edges[id].to;
		if (dist[to] == dist[v] + 1 && edges[id].c - edges[id].f >= flow) {
			long long pushed = dfs(to, flow);
			if (pushed) {
				edges[id].f += flow;
				edges[id ^ 1].f -= flow;
				return true;
			}
		}
	}
	return false;
}

long long maxFlow(long long source, long long target) {
	s = source;
	t = target;
	flow = 0;
	pt = vector<long long>(adjList.size());
	dist = vector<long long>(adjList.size());
	for (lim = (1LL  << 62); lim >= 1;) {
		if (!bfs()) {lim /= 2; continue;}
		for (long long i = 0; i < adjList.size(); i++) pt[i] = 0;
		long long pushed;
		while ((pushed = dfs(s, lim))) {
			flow += lim;
		}
	}
	return flow;
}

struct weaver {
	long long x, y, f, r;
};

struct place {
	long long x, y, f;
};

long long sq(long long x) {
	return x * x;
}

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);
	long long t;
	cin >> t;
	for (long long i = 0; i < t; i++) {
		long long w, p;
		cin >> w >> p;
		adjList = vector<vector<long long>>(2 + p + w - 1);
		vector<weaver> weavers(w);
		for (long long j = 0; j < w; j++) {
			cin >> weavers[j].x >> weavers[j].y >> weavers[j].f >> weavers[j].r;
		}
		vector<place> places(p);
		long long free = 0;
		for (long long j = 0; j < p; j++) {
			cin >> places[j].x >> places[j].y >> places[j].f;
			long long d = sq(weavers[0].x - places[j].x) + sq(weavers[0].y - places[j].y);
			if (d <= sq(weavers[0].r)) {
				weavers[0].f += places[j].f;
			} else {
				bool reachable = false;
				for (long long k = 1; k < w && !reachable; k++) {
					d = sq(weavers[k].x - places[j].x) + sq(weavers[k].y - places[j].y);
					reachable |= d <= sq(weavers[k].r);
				}
				if (reachable) {
					addEdge(0, 2 + j, places[j].f);
					free += places[j].f;
				}
			}
		}
		bool ok = true;
		for (long long j = 1; j < w; j++) {
			ok &= (weavers[0].f - weavers[j].f) >= 0;
			addEdge(2 + p + j - 1, 1, weavers[0].f - weavers[j].f);
			for (long long k = 0; k < p; k++) {
				long long d = sq(weavers[j].x - places[k].x) + sq(weavers[j].y - places[k].y);
				if (d <= sq(weavers[j].r)) {
					addEdge(2 + k, 2 + p + j - 1, INF);
				}
			}
		}
		if (ok) {
			ok &= free == maxFlow(0, 1);
		}
		if (ok) {
			cout << "Suiting Success" << endl;
		} else {
			cout << "Lonesome Willy" << endl;
		}
	}	
}
