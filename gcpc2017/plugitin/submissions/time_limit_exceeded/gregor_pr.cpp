// 
// 
#include <list>
#include <stack>
#include <queue>
#include <set>
#include <map>
#include <algorithm>
#include <iostream>
#include <sstream>
#include <cstdio>
#include <cstdlib>
#include <cmath>
#include <cstring>
#include <cfloat>
#include <climits>
#include <numeric>
#include <iomanip>

using namespace std;

const int oo = 0x3f3f3f3f;
const double eps = 1e-9;
const double PI = 2.0 * acos(0.0);


typedef long long ll;
typedef unsigned long long ull;
typedef pair<int, int> pii;
typedef vector<int> vi;
typedef vector<string> vs;

#define sz(c) int((c).size())
#define all(c) (c).begin(), (c).end()
#define FOR(i,a,b) for (int i = (a); i < (b); i++)
#define FORS(i,a,b,s) for (int i = (a); i < (b); i=i+(s))
#define FORD(i,a,b) for (int i = int(b)-1; i >= (a); i--)
#define FORIT(i,c) for (__typeof__((c).begin()) i = (c).begin(); i != (c).end(); i++)


struct edge {
	int to, cap, flow, oi;
};

#define MAXN 40000

vector<edge> adj[MAXN];
int h[MAXN];
int e[MAXN];
int act[MAXN];

int currentD;

void addEdge(int u, int v, int capUV, int capVU) {
	edge uv, vu;
	uv.to = v;
	uv.cap = capUV;
	uv.flow = 0;
	uv.oi = adj[v].size();

	vu.to = u;
	vu.cap = capVU;
	vu.flow = 0;
	vu.oi = adj[u].size();

	adj[u].push_back(uv);
	adj[v].push_back(vu);
}


priority_queue<pii> active;


void push(int u, int nei, int t){
	int delta = min(e[u], adj[u][nei].cap - adj[u][nei].flow);
	adj[u][nei].flow += delta;
	adj[adj[u][nei].to][adj[u][nei].oi].flow -= delta;
	e[u] -= delta;
	if (e[adj[u][nei].to] == 0 && adj[u][nei].to != t) active.push(make_pair(h[adj[u][nei].to],adj[u][nei].to));
	e[adj[u][nei].to] += delta;
}
int relCount;
void relable(int u){
	relCount++;
	h[u] = oo;
	FORIT(n,adj[u])
		if (n->flow < n->cap)
			h[u] = min(h[u], h[n->to]);
	h[u]++;
}
void discharge(int u, int t){
	while (e[u])
		if (act[u] == sz(adj[u])){
			relable(u);
			act[u] = 0;
		} else {
			if (adj[u][act[u]].cap - adj[u][act[u]].flow > 0 && h[u] > h[adj[u][act[u]].to])
				push(u,act[u],t);
			else
				act[u]++;
		}
}

void backBFS(int s, int t, int n){
	queue<pii> q;
	q.push(make_pair(t,0));
	FOR(i,0,n) h[i] = -1;
	h[s] = n;
	h[t] = 0;
	while (sz(q)){
		pii no = q.front(); q.pop();
		FORIT(i,adj[no.first]) if (h[i->to] == -1) if (adj[i->to][i->oi].cap > adj[i->to][i->oi].flow)
			h[i->to] = no.second+1, q.push(make_pair(i->to,no.second + 1));
	}
	// set unreachable nodes to height n+1
	int nr = 0;
	FOR(i,0,n) if (h[i] == -1) h[i] = n+1, nr++;
	// rebuild active queue
	while (sz(active)) active.pop();
	FOR(i,0,n) if (i != s && i != t && e[i]) active.push(make_pair(h[i],i));
}


int pushrelable(int s, int t, int n){
	FOR(i,0,n) e[i] = act[i] = 0, h[i] = -1;
	FOR(i,0,n) FORIT(n,adj[i]) n->flow = 0;
	h[s] = n;
	e[s] = oo;
	h[n] = -1;
	e[n] = 0; // just for convenience
	
	backBFS(s,t,n);
	
	while (sz(active)) active.pop();
	FOR(i,0,sz(adj[s])) if (adj[s][i].cap){
		push(s,i,t);
		int to = adj[s][i].to;
		if (h[to] > 0) active.push(make_pair(h[to],to));
	}

	relCount = 0;
	while (sz(active)){
		pii no = active.top();
		active.pop();
		if (!e[no.second]) continue;
		discharge(no.second,t);
		
		if (e[no.second]) active.push(make_pair(h[no.second],no.second));
		if (relCount/2 % n == n-1) backBFS(s,t,n), relCount = 0;
	}
	
	int flow = 0;
	FORIT(n,adj[s]) flow+=n->flow;
	return flow;
}


int main(){
	int N,M,K; cin >> M >> N >> K;
	// base graph
	FOR(i,0,M) addEdge(0,2+i,1,0);
	FOR(i,0,N) addEdge(2+M+i,1,1,0);

	FOR(i,0,K){
		int x,y; cin >> x >> y;
		x--, y--;
		addEdge(2+x,2+M+y,1,0);
	}

	// baseline 
	int base = pushrelable(0,1,2+M+N);
	
	FOR(i,0,M){
		addEdge(0,2+i,2,0);
		int cur = pushrelable(0,1,2+M+N);
		if (cur > base) base = cur;
		adj[0].pop_back();
		adj[2+i].pop_back();

	}

	cout << base << endl;
	
}


























