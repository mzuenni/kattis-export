#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
#define FOR(i,a,b) for (ll i = (a); i < (b); i++)
#define sz(c) ll((c).size())
#define pb push_back

struct edge { ll to, cap; };

ll n, m, N, s, t;
vector<vector<ll>> adj;
vector<edge> edges;
vector<bool> mark;

bool dfs(ll x) {
	if (x == t) return true;
	mark[x] = true;
	for (ll &i : adj[x]) if (!mark[edges[i].to]) {
		if (edges[i].cap && dfs(edges[i].to)) {
			edges[i].cap--, edges[i^1].cap++;
			return true;
		}
	}
	return false;
}

bool check(ll d) {
	FOR(i,0,n) edges[2*i].cap = d, edges[2*i+1].cap = 0;
	FOR(i,n,n+3*m) edges[2*i].cap = 1, edges[2*i+1].cap = 0;
	fill(begin(mark),end(mark),false);
	
	ll flow = 0;
	while (flow < m && dfs(s)) flow++, fill(begin(mark),end(mark),false);
	return flow == m;
}

void add_edge(ll a, ll b, ll c) {
	adj[a].pb(sz(edges));
	edges.pb({b,c});
	adj[b].pb(sz(edges));
	edges.pb({a,0});
}

int main() {
	cin >> n >> m;
	N = m+n+2, s = m+n, t = m+n+1;
	vector<ll> a(m), b(m);
	FOR(i,0,m) cin >> a[i] >> b[i];
	FOR(i,0,m) a[i]--;
	FOR(i,0,m) b[i]--;
	adj.resize(N), mark.resize(N);
	edges.reserve(2*n+6*m);
	FOR(i,0,n) add_edge(m+i,t,0);
	FOR(i,0,m) add_edge(s,i,1);
	FOR(i,0,m) add_edge(i,m+a[i],1), add_edge(i,m+b[i],1);

	ll dmin = -1, dmax = n;
	while (dmax-dmin > 1) {
		ll d = (dmin+dmax)/2;
		if (check(d)) dmax = d; else dmin = d;
	}
	cout << dmax << endl;
}
