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

int dp[300001][11];

int main(){
	int n,m; cin >> n >> m;
	FOR(i,0,m+1) FOR(t,0,n+1) dp[t][i] = -oo;
	dp[0][0] = 0;
	FOR(t,1,n+1){
		int p; cin >> p;
		// use the weapon
		dp[t][1] = max(dp[t-1][m] + p,dp[t-1][0]);
		FOR(i,2,m+1) dp[t][i] = dp[t-1][i-1];
		dp[t][m] = max(dp[t-1][m],dp[t][m]);
	}
	int r = 0;
	FOR(i,0,m+1) r = max(r,dp[n][i]);
	cout << r << endl;
	
	/*FOR(t,0,n+1){
		cout << "time " << t << ":";
		FOR(i,0,m+1) cout << " " << dp[t][i];
		cout << endl;
	}*/
}












