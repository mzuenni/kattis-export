#include <list>
#include <map>
#include <stack>
#include <queue>
#include <set>
#include <sstream>
#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cmath>
#include <cstdlib>
#include <cstring>
#include <climits>
#include <cfloat>
#include <numeric>
#include <iomanip>
#include <cassert>
#include <unordered_set>
#include <unordered_map>
#include <bitset>
#include <tuple>
using namespace std;

typedef long long ll;
typedef vector<int> vi;
typedef vector<string> vs;
typedef pair<int,int> pii;

const int oo = 0x3f3f3f3f;
const double eps = 1e-9;

#define sz(c) int((c).size())
#define all(c) (c).begin(), (c).end()
#define FOR(i,a,b) for (int i = (a); i < (b); i++)
#define FORD(i,a,b) for (int i = int(b)-1; i >= (a); i--)
#define FORIT(i,c) for (auto i=(c).begin(); i!=(c).end(); i++)
#define mp make_pair
#define pb push_back
#define has(c,i) ((c).find(i) != (c).end())
#define DBG(...) ({ if(1) fprintf(stderr, __VA_ARGS__); })
#define DBGDO(X) ({ if(1) cerr << "DBGDO: " << (#X) << " = " << (X) << endl; })

const int maxN = 514;
int x[maxN];
int y[maxN];
double dist[maxN][maxN];
double distSum[maxN][maxN];
double dp[maxN][maxN];

double rec(int i, int j) {
	if (i == 0) return distSum[i][j];
	if (dp[i][j] >= 0) return dp[i][j];

	if (i+1 == j) {
		double best = 100000000;
		FOR(k,0,i) {
			best = min(best, rec(k,i) + dist[k][j]);
		}
		dp[i][j] = best;
		return best;
	} else {
		dp[i][j] = rec(i,i+1) + distSum[i+1][j];
		return dp[i][j];
	}
}

int main() { 
	ios_base::sync_with_stdio(false); 
	
	int T;
	cin >> T;
	FOR(t,0,T) {
		int N;
		cin >> N;
		FOR(i,0,N) 	cin >> x[i+1] >> y[i+1];
		x[0] = x[1]; y[0] = y[1];
		x[N+1] = x[N]; y[N+1] = y[N];
		
		FOR(i,0,N+2) FOR(j,i+1,N+2)
			dist[i][j] = sqrt((x[i]-x[j])*(x[i]-x[j]) + (y[i]-y[j])*(y[i]-y[j]));
		FOR(i,0,N+2) {
			distSum[i][i] = 0;
			FOR(j,i+1,N+2) distSum[i][j] = distSum[i][j-1] + dist[j-1][j];
		}
		FOR(i,0,N+2) FOR(j,i+1,N+2) dp[i][j] = -1;

		cout << rec(N,N+1) << endl;

	}

}


