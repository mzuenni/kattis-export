#include <bits/stdc++.h>

using namespace std;

#define all(x) begin(x), end(x)
#define sz(x) (ll)(x).size()

using ll = long long;
using ld = long double;

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);
	ll n, l, r;
	cin >> n >> l >> r;
	n++;
	vector<ll> in(n);
	for (ll i = 0; i < n; i++) cin >> in[i];
	reverse(in.begin()+l, in.end());
	ll res = 0;
	for (ll it : {0, 1}) {
		ll i = 0;
		while (in[i] != 0) i++;
		for (ll ma = 0; i < n; i++) {
			if (in[i] > ma) {
				res++;
				ma = in[i];
			}
		}
		reverse(all(in));
	}
	cout << res << endl;
}
