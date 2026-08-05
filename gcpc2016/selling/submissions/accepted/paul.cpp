#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef vector<ll> vl;
#define FOR(i,a,b) for (ll i = (a); i < (b); i++)
#define FORD(i,a,b) for (ll i = (b)-1; i >= (a); i--)

int main() {
	ll c, m; cin >> c >> m;

	vl dp(c+1);
	FOR(i,0,m) {
		vl a(c+1);
		FOR(j,1,c+1) cin >> a[j];
		FORD(j,1,c+1) FOR(k,1,j+1) dp[j] = max(dp[j],dp[j-k] + a[k]);
	}
	cout << dp[c] << endl;
}

