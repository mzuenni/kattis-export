#include <bits/stdc++.h>
using namespace std;

#define all(x) begin(x), end(x)
#define sz(x) (ll)(x).size()

using ll = long long;
using ld = long double;

array<ll, 5> val = {4,6,8,12,20};

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);

	vector<ll> in(sz(val));
	for (ll& x : in) cin >> x;

	ll l = 0;
	ll r = 0;
	for (ll i = 0; i < sz(in); i++) {
		l += in[i];
		r += in[i] * val[i];
	}

	vector<ll> res;
	for (; l <= r; l++, r--) {
		res.push_back(l);
		if (l != r) res.push_back(r);
	}
	reverse(all(res));

	for (ll x : res) cout << x << " ";
	cout << endl;
}
