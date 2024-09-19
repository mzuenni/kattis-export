#include <bits/stdc++.h>
using namespace std;
typedef vector<int> vi;
#define FOR(i,a,b) for (int i = (a); i < (b); i++)
#define FORIT(i,c) for (__typeof__((c).begin()) i = (c).begin(); i != (c).end(); i++)

vi adj[1000000];
int col[1000000];

bool cycle = false;

void dfs(int i, int mycol){
	if (col[i] == 1-mycol) cycle = true;
	if (col[i] != 2) return;
	col[i] = mycol;
	FORIT(j,adj[i]) dfs(*j,1-mycol);
}

int main(){
	int N, M, P; cin >> N >> M >> P;
	FOR(i,0,M) {
		int a,b; cin >> a >> b;
		a--, b--;
		adj[a].push_back(b);
		adj[b].push_back(a);
	}
	FOR(i,0,N) col[i] = 2;
	int num = 0;
	FOR(i,0,N) if (col[i] == 2) dfs(i,0), num++;

	if (cycle) cout << "impossible" << endl;
	else {
		long long ans = 1;
		FOR(i,0,num-1) ans = (ans << 1) % P;
		ans = (ans+1) % P;
		cout << ans << endl;
	}
}
