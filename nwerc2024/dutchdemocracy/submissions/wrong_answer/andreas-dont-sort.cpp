#include <iostream>
#include <numeric>
#include <vector>
using namespace std;
using ll = long long;

int main() {
	cin.tie(0);
	ios_base::sync_with_stdio(0);

	int n;
	cin >> n;
	vector<ll> p(n);
	for (int i = 0; i < n; i++) cin >> p[i];

	ll t = accumulate(p.begin(), p.end(), 0LL)/2 + 1;
	vector<ll> dp(t);
	dp[0] = 1;
	
	ll res = 0;
	for (int i = 0; i < n; i++) {
		for (ll votes = t-1; votes >= 0; votes--) {
			if (votes + p[i] >= t)
				res += dp[votes];
			else
				dp[votes + p[i]] += dp[votes];
		}
	}
	cout << res << endl;
}
