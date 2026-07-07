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


int n;
vi adj[2000];
bool v[2000];

void dfs(int rat, int rav){
	if (v[rat]) return;
	v[rat] = true;
	FORIT(j,adj[rat]) if (*j != rav) dfs(*j,rav);
}

int cc[2000];
int dd[2000];

int bestP(int rat, int rav){
	//cout << "RAT " << rat << " RAV " << rav << endl;
	// find all leafs below rat not passing rav
	if (rat != -1){
		FOR(i,0,n) v[i] = false;
		dfs(rat,rav);
	} else {
		FOR(i,0,n) v[i] = true;
	}
	// run longest path DP
	queue<int> q;
	FOR(i,0,n) cc[i] = dd[i] = 0;
	FOR(i,0,n) if (sz(adj[i]) == 1 && v[i]) q.push(i), dd[i] = 1; // this is a leaf
	int maxi = 1;
	while (sz(q)){
		int i = q.front(); q.pop();
		FORIT(j,adj[i]) if (!dd[*j] && v[*j]){ // if not yet assigned a value and reachable
			cc[*j]++; // increase number of handled neighbours
			
			if (cc[*j] == sz(adj[*j]) - 1) {
				// compute the distance value of the node
				FORIT(k,adj[*j]) dd[*j] = max(dd[*j], 1+dd[*k]);
				maxi = max(maxi, dd[*j]);
				q.push(*j);
			}
		}
	}
	return maxi;
}


int main(){
	int r,h,m; cin >> n >> r >> h >> m;
	r--, h--, m--;
	FOR(i,0,n-1){
		int x,y; cin >> x >> y;
		x--, y--;
		adj[x].push_back(y);
		adj[y].push_back(x);
	}
	
	cout << min(bestP(r,h) , min ( bestP(r,m) , bestP(-1,-1) ) ) << endl;
    return 0;
}
