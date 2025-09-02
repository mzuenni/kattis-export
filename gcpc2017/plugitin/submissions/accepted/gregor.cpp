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

#define MAXN 30000

vi adj[MAXN];
int mat[MAXN];
int l[MAXN];

void bfs(int a, int b){
	queue<int> q;
	FOR(i,0,a+b) l[i] = -1;
	FOR(i,0,a) if (mat[i] == -1) q.push(i), l[i] = 0;
	while (sz(q)){
		int i = q.front(); q.pop();
		FORIT(j,adj[i]) if (l[*j] == -1) {
			//cout << "BFS " << i << " to " << *j << " M " << mat[i] << " " << mat[*j] << endl; 
			if (i < a) { // can only traverse unmatched edges
				if (mat[i] == -1 || mat[i] != *j)
					l[*j] = l[i]+1, q.push(*j);
			} else { // can only traverse matched edges
				if (mat[i] != -1 && mat[i] == *j)
					l[*j] = l[i]+1, q.push(*j);
			}
		}
	}
	//FOR(i,0,a+b) cout << i << " L " << l[i] << endl;
}


bool v[MAXN];
stack<int> path;

bool _dfs(int a, int b, int i){
	if (v[i]) return false;
	//cout << "DFS " << i << endl;
	v[i] = true; path.push(i);
	if (i < a && mat[i] == -1) return true; // if we reached an unmatched node on the left, we are done

	FORIT(j,adj[i]) if (l[*j] == l[i]-1) { // only go to lower layers
		//cout << "NEI " << *j << endl;
		if (i < a) { // can only traverse matched edges
			if (mat[i] != -1 && mat[i] == *j)
				if (_dfs(a,b,*j)) return true;
		} else { // can only traverse unmatched edges
			if (mat[i] == -1 || mat[i] != *j)
				if (_dfs(a,b,*j)) return true;
		}
	}
	path.pop(); // remove myself
	return false;
}

bool dfs(int a, int b){
	bool didSomething = false;
	FOR(i,0,a+b) v[i] = false;
	FOR(i,a,a+b) if (mat[i] == -1 && _dfs(a,b,i)){
		// augment path
		int last = -1;
		//cout << "PATH " << sz(path) << endl;
		while (sz(path)){
			int j = path.top(); path.pop();
			if (j >= a) {
				mat[j] = last, mat[last] = j;
				//cout << "M " << j << " & " << last << endl;
			}
			else last = j;
		}
		didSomething = true;
	}
	//FOR(i,0,a+b) cout << "MAT " << i << " " << mat[i] << endl;
	return didSomething;
}


int hk(int a, int b){ // size of a and size of b
	FOR(i,0,a+b) mat[i] = -1;
	//cout << endl << endl << endl << "HK" << endl;
	do {
		//cout << "ROUND" << endl;
		// layering
		bfs(a,b);
	} while (dfs(a,b));

	// count matching
	int s = 0;
	FOR(i,0,a) if (mat[i] != -1) s++;
	//cout << s << endl;
	return s;
}


int bm[MAXN];

int main(){
	int N,M,K; cin >> M >> N >> K;

	FOR(i,0,K){
		int x,y; cin >> x >> y;
		x--, y--;
		adj[N+x].push_back(y);
		adj[y].push_back(N+x);
	}

	FOR(i,0,N+M) mat[i] = -1;
	int base = hk(N,M);
	if (base == N) {
		cout << base << endl;
		return 0;
	}
	FOR(i,0,N+M) bm[i] = mat[i];
	bm[N+M] = bm[N+M+1] = -1;

	int best = base;
	
	FOR(i,0,M) if (bm[N+i] != -1) {
		FOR(i,0,N+M+2) mat[i] = bm[i]; // restore
		// add edges
		FORIT(j,adj[N+i]){
				//cout << "CONN " << *j;
				adj[N+M].push_back(*j), adj[*j].push_back(N+M),
				adj[N+M+1].push_back(*j), adj[*j].push_back(N+M+1);
		}

		int cur = hk(N,M+2);
		if (cur > best) best  = cur;
		
		FORIT(j,adj[N+i]) adj[*j].pop_back(), adj[*j].pop_back();
		adj[N+M].clear();
		adj[N+M+1].clear();

		if (best == N || best == base+2) break;
	}

	cout << best << endl;
	
}




