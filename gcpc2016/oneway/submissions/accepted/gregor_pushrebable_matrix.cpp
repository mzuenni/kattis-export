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
	int cap, flow;
};

#define MAXN 6000

edge adj[MAXN][MAXN];
int h[MAXN];
int e[MAXN];

int in[MAXN];

int currentD;

priority_queue<pii> active;

void push(int u, int v){
	int delta = min(e[u], adj[u][v].cap - adj[u][v].flow);
	adj[u][v].flow += delta;
	adj[v][u].flow -= delta;
	e[u] -= delta;
	if (e[v] == 0 && v != 1) active.push(make_pair(h[v],v));
	e[v] += delta;
}

void relable(int u, int n){
	h[u] = oo;
	FOR(v,0,n)
		if (adj[u][v].flow < adj[u][v].cap)
			h[u] = min(h[u], h[v]);
	h[u]++;
}

void discharge(int u, int n){
	int v = 0;
	while (e[u])
		if (v == n){
			relable(u,n);
			v = 0;
		} else {
			if (adj[u][v].cap - adj[u][v].flow > 0 && h[u] > h[v])
				push(u,v);
			else
				v++;
		}
}

/*void backBFS(int t){
	queue<pii> q;
	q.push(make_pair(t,0));
	
	while (sz(q)){
		pii n = q.front(); q.pop();
		h[n.first] = n.second;
		
		FOR(i,0,2+N) if (h[i->to] == -1) if (adj[i->to][i->oi].cap)
			q.push(make_pair(i->to,n.second + 1));
	}
}*/

int pushrelable(int s, int t, int n){
	FOR(i,0,n) e[i] = 0, h[i] = 0;
	FOR(i,0,n) FOR(j,0,n) adj[i][j].flow = 0;
	h[s] = n;
	e[s] = oo;
	h[n] = -1;
	e[n] = 0; // just for convenience
	
	//backBFS(t);
	
	while (sz(active)) active.pop();
	FOR(i,0,n) if (i != s) {
		push(s,i);
		if (h[i] > 0) active.push(make_pair(h[i],i));
	}

	while (sz(active)){
		//cout << "GO" << endl;
		//FOR(i,0,n) cout << "E " << i << " -> " << e[i] << endl;
		pii no = active.top();
		active.pop();
		discharge(no.second,n);
		
		if (e[no.second]) active.push(make_pair(h[no.second],no.second));
	}
	
	int flow = 0;
	FOR(i,0,n) flow += adj[0][i].flow;
	return flow;
}


int main(){
	int N,M; cin >> N >> M;
	FOR(i,0,N) in[i] = 0;
	
	FOR(i,0,M){
		int x,y;
		cin >> x >> y;
		x--,y--;
		if (x < y)
			adj[2+x][2+y].cap = 1, in[2+x]++;
		else
			adj[2+y][2+x].cap = 1, in[2+y]++;
	}

	
	int hi = M+1;
	int lo = -1;
	while (lo+1 < hi){
		currentD = (lo+hi)/2;
		//cout << currentD << endl;
		FOR(i,2,2+N) adj[0][i].cap = max(0,in[i]-currentD);
		FOR(i,2,2+N) adj[i][1].cap = max(0,currentD-in[i]);
		
		int mf = pushrelable(0,1,2+N);
		int tgt = 0;
		FOR(i,0,N)
			tgt += max(0,in[2+i]-currentD);
		if (mf == tgt)
			hi = currentD;
		else
			lo = currentD;
	}
	
	cout << hi << endl;
}


























