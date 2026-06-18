#include <bits/stdc++.h>
using namespace std;

#define all(x) begin(x), end(x)
#define sz(x) (ll)(x).size()

using ll = long long;
using ld = long double;

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);

	ll n, k;
	cin >> n >> k;
	vector<vector<ll>> children(n);
	for (ll i = 1; i < n; i++) {
		ll p;
		cin >> p;
		children[p - 1].push_back(i);
	}
	std::vector<ll> res;
	auto dfs = [&](auto&& self, ll c) -> ll {
		ll d = 0;
		for (ll x : children[c]) {
			d = max(d, self(self, x));
		}
		if (c == 0 or d == k - 1) {
			res.push_back(c);
			return 0;
		} else {
			return d + 1;
		}
	};
	dfs(dfs, 0);

	cout << sz(res) << endl;
	for (ll x : res) cout << x+1 << " ";
	cout << endl;
}