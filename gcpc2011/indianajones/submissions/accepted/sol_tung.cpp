#include <bits/stdc++.h>

using namespace std;

#define foru(i,l,r)		for(int i=l; i<=r; i++)
#define ford(i,r,l)		for(int i=r; i>=l; i--)
#define fs				first
#define sc 				second
#define	pb				push_back

#define maxn			100011

int 	n,	m,  ncnt;
int  	ordered;
int 	grad[maxn], res[maxn], number[maxn];
vector<int>		adj[maxn];
bitset<maxn>	visited, through;

void input() {
	cin >> n >> m;
	foru(i,1,n+1)
		adj[i].clear();

	fill(grad, grad+n+2, 0);

	int u, v;
	foru(i,1,m) {
		cin >> u >> v;
		adj[u].pb(v);
		grad[v]++;
	}
}

int visit(int u) {
	if (visited[u])
		return 0;

	visited[u] = 1;
	through[u] = 1;

	for(int v : adj[u]) {
		if (visited[v] == 1) {
			if (through[v] == 1)
				return -1;
		}
		else { 
			if (visit(v) == -1)
				return -1;
		}
	}

	through[u] = 0;
	return 0;
}

int solve() {
	
	visited.reset();
	through.reset();
	ncnt = 0;

	//check for circles
	foru(i,1,n)
		if (visited[i] == 0)
			if (visit(i) == -1)		//circle from here
				return 1;

	//topo sort
	queue<int> q;
	
	ordered = 0;
	foru(i,1,n) 
		if (grad[i] == 0)	q.push(i);

	while (!q.empty()) {
		if (q.size() > 1)
			return 2;

		int u = q.front();
		q.pop();
		res[++ordered] = u;

		for(int v : adj[u]) {
			grad[v]--;
			if (grad[v] == 0)
				q.push(v);
		}
	}

	return 0;
}

int main() {
	int test;
	cin >> test;
	while (test--) {
		input();
		int s = solve();
		if (s==0) {

			foru(i,1,n-1) 
				cout << res[i] << " ";
			cout << res[n] << endl;
		}
		else 
		if (s == 1)
			cout << "recheck hints" << endl;
			else cout << "missing hints" << endl;
	}
}