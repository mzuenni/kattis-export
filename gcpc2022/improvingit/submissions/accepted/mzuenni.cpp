#include <bits/stdc++.h>
using namespace std;

#define all(x) begin(x), end(x)
#define sz(x) (ll)(x).size()

using ll = long long;
using ld = long double;

constexpr ll inf = 0x3FFFFFFFFFFFFFFF;

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);
	ll n, m;
	cin >> n >> m;
	vector<ll> dp(n+1, inf);
	dp[0] = 0;
	for (ll i = 0; i < n; i++) {
		ll p;
		cin >> p;
		dp[i] += p;
		for (ll j = 1; j <= m && i+j <= n; j++) {
			ll x;
			cin >> x;
			dp[i+j] = min(dp[i+j], dp[i] - x);
		}
	}
	cout << dp[n] << endl;
}
