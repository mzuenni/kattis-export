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


int dfs(int i, int h, int m){
	if (v[i]) return 0;
	v[i] = true;
	int s = 1;
	FORIT(j,adj[i]) if (*j != h && *j != m) s += dfs(*j,h,m);
	return s;
}

int rr(int r, int h, int m){
	FOR(i,0,n) v[i] = false;
	return dfs(r,h,m);
}

int rav(int r, int h, int m);

int dpRAT[100][100][100];
int dpRAV[100][100][100];

int rat(int r, int onTree, int flying){
	if (dpRAT[r][onTree][flying] != -1) return dpRAT[r][onTree][flying];
	dpRAT[r][onTree][flying] = oo;
	//cout << "RAT " << r << " " << onTree << " " << flying << endl;
	// determine the fields to which ratatöskr can go
	rr(r,onTree,-1);
	bool* vv = new bool[n];
	FOR(i,0,n) vv[i] = v[i];

	int best = 0;
	vi ii,iii;
	FOR(i,0,n) if (vv[i]) {
		best = max(best,rav(i,onTree,flying));
		ii.push_back(rav(i,onTree,flying));
		iii.push_back(i);
	}
	delete[] vv;
	//cout << "RAT " << r << " " << onTree << " " << flying << ": " << best;
	//FOR(i,0,sz(ii)) cout << " " << iii[i] << "@" << ii[i];
	//cout << endl;
	return dpRAT[r][onTree][flying] = best;
}

int rav(int r, int h, int m){
	if (r == h || r == m) {/*cout << endl;*/ return 0;}
	if (dpRAV[r][h][m] != -1) return dpRAV[r][h][m];
	
	//dpRAV[r][h][m] = 0;
	
	// select the raven that is flying (i.e. the one that restricts Rat less)
	int hr = rr(r,h,-1);
	int mr = rr(r,m,-1);
	
	int best = oo;

	
	if (hr < mr){
		// let m fly
		rr(r,h,-1);
		//cout << " keep " << h << endl;
		bool* vv = new bool[n];
		FOR(i,0,n) vv[i] = v[i];
		FOR(i,0,n) if (i != m && vv[i]) best = min(best,rat(r,h,i));
		delete[] vv;
	} else {
		// let h fly
		rr(r,m,-1);
		//cout << " keep " << m << endl;
		bool* vv = new bool[n];
		FOR(i,0,n) vv[i] = v[i];
		FOR(i,0,n) if (i != h && vv[i]) best = min(best,rat(r,m,i));
		delete[] vv;
	}
	//cout << "RAV " << r << " " << h << " " << m << ": " << (1+best) << endl;
	return dpRAV[r][h][m] = 1 + best;
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
	FOR(i,0,n) FOR(j,0,n) FOR(k,0,n) dpRAT[i][j][k] = dpRAV[i][j][k] = -1;
	cout << rav(r,h,m) << endl;
}
