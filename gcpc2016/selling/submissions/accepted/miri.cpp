#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using vl = vector<ll>;
using vvl = vector<vl>;
using pll = pair<ll,ll>;
using vb = vector<bool>;
const ll oo = 0x3f3f3f3f3f3f3f3fLL;
const double eps = 1e-9;
#define sz(c) ll((c).size())
#define all(c) begin(c),end(c)
#define mp make_pair
#define mt make_tuple
#define pb push_back
#define eb emplace_back
#define xx first
#define yy second
#define has(c,i) ((c).find(i) != end(c))
#define FOR(i,a,b) for (int i=(a); i<(b); i++)       
#define FORD(i,a,b) for (int i=int(b)-1; i>=(a); i--)
#define DBGDO(X) ({ if(1) cerr << "DBGDO: " << (#X) << " = " << (X) << endl; })
ll p[110][110];
ll dp[110][110];

int main() { 
	ios::sync_with_stdio(false); 
	ll c, m;
	cin >> c >> m;
	FOR(i,0,m) FOR(j,0,c) cin >> p[i][j+1];
	FOR(i,0,m) dp[i][c] = 0;
	FOR(i,0,c+1) dp[0][i] = p[0][c-i];
	FOR(i,1,m){
		FOR(j,0,c+1){
			FOR(k,0,j+1){
				dp[i][j-k] = max(dp[i][j-k], dp[i-1][j] + p[i][k]);
			}
		}
	}
	ll ans = 0;
	FOR(i,0,c+1) ans = max(ans, dp[m-1][i]);
	cout << ans << endl;
}
