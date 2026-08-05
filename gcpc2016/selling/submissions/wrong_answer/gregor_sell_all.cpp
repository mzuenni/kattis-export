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

// merchants handled, CPUs sold
int dp[101][101];

int p[101];


int main(){
	int c,m; cin >> c >> m;
	FOR(i,0,c+1) dp[0][i] = -oo;
	dp[0][0] = 0;
	FOR(i,1,m+1) {
		FOR(j,1,c+1) cin >> p[j];
		FOR(j,0,c+1){
			dp[i][j] = dp[i-1][j];
			FOR(k,1,j+1) dp[i][j] = max(dp[i][j], dp[i-1][j-k] + p[k]);
		}
	}
	cout << dp[m][c] << endl;
}
