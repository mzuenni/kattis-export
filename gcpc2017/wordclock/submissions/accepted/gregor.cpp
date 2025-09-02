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

string w[30];
string ww[30];
bool ss[30];

int dp[1<<22][30]; // min position for a given subset of string and the last string
int dprev[1<<22][30];
int ol[30][30];


int overlap(int x, int y){
	if (ol[x][y] != -1) return ol[x][y];
	FOR(i,0,sz(w[x])){
		int ok = true;
		FOR(j,0,min(sz(w[x]) - i, sz(w[y]))) ok &= w[x][i+j] == w[y][j];
		if (ok) return ol[x][y]=i;
	}
	return ol[x][y]=sz(w[x]);
}

char f[10000];

int main(){
	int H,W,n; cin >> H >> W >> n;
	FOR(i,0,n) cin >> ww[i];
	
	FOR(i,0,n) FOR(j,0,n) if (i != j && ww[i].find(ww[j]) != string::npos) ss[j] = true;
	
	int N = 0;
	w[N++] = "";
	FOR(i,0,n) if (!ss[i]) w[N++] = ww[i];
	FOR(i,0,N) FOR(j,0,N) ol[i][j] = -1;
	
	FOR(i,1,N+1) dp[0][i] = H*W+1;
	dp[0][0] = 0;
	FOR(S,1,1<<N) FOR(j,0,N) {
		// we *want* to add j last
		if (!(S%2) || !(S & (1 << j)) || sz(w[j]) > W) dp[S][j] = H*W+1;
		else {
			// I don't know which of the last ones was the last before
			dp[S][j] = H*W+1;
			
			FOR(l,0,N) if ((l != j || !l) && (S & (1 << l))){ // if not the current one and part of the set
				int oldVal = dp[S - (1 << j)][l];
				//cout << "try " << l << " value " << oldVal << endl;
				if (oldVal > H*W) continue;
				// get substring info
				int sub = sz(w[l]) - overlap(l,j);
				//cout << "sub " << sub << " " << l << " " << j << endl;
				// test whether we can still fit into the current line
				int val = H*W+1;
				if (oldVal % W && (oldVal % W) + sz(w[j]) - sub <= W)
					val = oldVal + sz(w[j]) - sub;
				else if (oldVal % W)
					val = oldVal - (oldVal % W) + W + sz(w[j]);
				else
					val = oldVal + sz(w[j]);
				if (val < dp[S][j])
					dp[S][j] = val, dprev[S][j] = l;
			}
			//if ((S - 1)%1000 == 0) cout << "S " << S << " j " << j << " dp " << dp[S][j] << endl;
		}
	}
	
	
	
	FOR(i,0,N) if (dp[(1 << N)-1][i] <= H*W) {
		//cout << i << ": " << dp[(1 << N)-1][i] << endl;
		FOR(h,0,H) FOR(w,0,W) f[h*W + w] = 'X';
		// backtrace
		int S = (1 << N)-1;
		int j = i;
		while (S){
			int firstPos = dp[S][j] - sz(w[j]);
			FOR(k,0,sz(w[j])) f[firstPos + k] = w[j][k];
		
			int nS = S - (1 << j);
			int nj = dprev[S][j];
			S = nS;
			j = nj;
		}
		
		FOR(h,0,H){
			FOR(w,0,W) cout << f[h*W + w];
			cout << endl;
		}
		return 0;
	}
	cout << "impossible" << endl;
}












