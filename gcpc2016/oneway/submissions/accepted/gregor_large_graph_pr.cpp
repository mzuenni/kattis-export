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

#define MAXN 1000000

vector<edge> adj[MAXN];
int h[MAXN];
int e[MAXN];
int act[MAXN];

int in[MAXN];

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


void push(int u, int nei){
	int delta = min(e[u], adj[u][nei].cap - adj[u][nei].flow);
	adj[u][nei].flow += delta;
	adj[adj[u][nei].to][adj[u][nei].oi].flow -= delta;
	e[u] -= delta;
	if (e[adj[u][nei].to] == 0 && adj[u][nei].to != 1) active.push(make_pair(h[adj[u][nei].to],adj[u][nei].to));
	e[adj[u][nei].to] += delta;
}

void relable(int u){
	h[u] = oo;
	FORIT(n,adj[u])
		if (n->flow < n->cap)
			h[u] = min(h[u], h[n->to]);
	h[u]++;
}

void discharge(int u){
	while (e[u])
		if (act[u] == sz(adj[u])){
			relable(u);
			act[u] = 0;
		} else {
			if (adj[u][act[u]].cap - adj[u][act[u]].flow > 0 && h[u] > h[adj[u][act[u]].to])
				push(u,act[u]);
			else
				act[u]++;
		}
}

void backBFS(int t){
	queue<pii> q;
	q.push(make_pair(t,0));
	
	while (sz(q)){
		pii n = q.front(); q.pop();
		h[n.first] = n.second;
		
		FORIT(i,adj[n.first]) if (h[i->to] == -1) if (adj[i->to][i->oi].cap)
			q.push(make_pair(i->to,n.second + 1));
	}
}

int pushrelable(int s, int t, int n){
	FOR(i,0,n) e[i] = act[i] = 0, h[i] = -1;
	FOR(i,0,n) FORIT(n,adj[i]) n->flow = 0;
	h[s] = n;
	e[s] = oo;
	h[n] = -1;
	e[n] = 0; // just for convenience
	
	backBFS(t);
	
	while (sz(active)) active.pop();
	FOR(i,0,sz(adj[s])){
		push(s,i);
		int to = adj[s][i].to;
		if (h[to] > 0) active.push(make_pair(h[to],to));
	}

	while (sz(active)){
		pii n = active.top();
		active.pop();
		discharge(n.second);
		
		if (e[n.second]) active.push(make_pair(h[n.second],n.second));
	}
	
	int flow = 0;
	FORIT(n,adj[s]) flow+=n->flow;
	return flow;
}





int main(){
	int N,M; cin >> N >> M;
	FOR(i,0,M){
		int x,y;
		cin >> x >> y;
		x--,y--;
		addEdge(0,2+N+i,1,0);
		addEdge(2+N+i,2+x,1,0);
		addEdge(2+N+i,2+y,1,0);
	}
	FOR(i,0,N) addEdge(2+i,1,oo,0);
	
	int hi = M+1;
	int lo = -1;
	while (lo+1 < hi){
		currentD = (lo+hi)/2;
		FOR(i,0,sz(adj[1])){
			int from = adj[1][i].to;
			int oi = adj[1][i].oi;
			adj[from][oi].cap = currentD;
		}
		int mf = pushrelable(0,1,2+N+M);
		if (mf == M)
			hi = currentD;
		else
			lo = currentD;
	}
	
	cout << hi << endl;
}


























