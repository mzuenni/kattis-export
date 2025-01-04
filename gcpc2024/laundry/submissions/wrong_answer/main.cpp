#include <bits/stdc++.h>
using namespace std;

#define all(x) begin(x), end(x)
#define sz(x) (ll)(x).size()

using ll = long long;
using ld = long double;

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);
	ll t; 
	cin >> t; 
	while (t--) {
		ll k;
		cin >> k;
		vector<ll> in(8);
		cin >> in[1] >> in[2] >> in[4] >> in[3] >> in[6] >> in[5] >> in[7];
		ll req = 0;
		for (ll& x : in) {
			req += x / k;
			x %= k;
		}
		vector<ll> s = {1, 2, 4};
		ll res = 9;
		do {
			ll a = in[7];
			ll cur = 0;
			ll carry = 0;
			for (ll i : {0, 1, 2}) {
				carry += in[s[i]];
				ll x = (carry + k - 1) / k;
				carry += in[s[i] | s[(i + 1) % 3]] - k * x;
				if (carry < 0) {
					a = max(0ll,a+carry);
					carry = 0;
				}
				cur += carry / k + x;
				carry %= k;
			}
			cur += (carry + a + k - 1) / k;
			res = min(res, cur);
		} while (next_permutation(all(s)));
		cout << req+res << endl;
	}
}
