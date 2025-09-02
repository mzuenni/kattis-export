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
typedef long double ld;
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

ld dp[1000][1000];

int main(){
	int n,m; cin >> n >> m;
	FOR(i,0,n) FOR(j,0,n) dp[i][j] = 0.0;
	FOR(i,0,m){
		int x,y; ld v; cin >> x >> y >> v;
		x--,y--;
		dp[x][y] = v;
	}

	// run FW
	FOR(i,0,n) FOR(j,0,n) FOR(k,0,n) dp[i][j] = max(dp[i][j], dp[i][k]*dp[k][j]);
	
	bool bad = false;
	FOR(i,0,n) bad = bad || (dp[i][i] > 1);

	if (bad) cout << "inadmissible" << endl; else cout << "admissible" << endl;
}
