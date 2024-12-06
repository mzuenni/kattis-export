#include <bits/stdc++.h>
using namespace std;

#define all(x) begin(x), end(x)
#define sz(x) (ll)(x).size()

using ll = long long;
using ld = long double;

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);

	ll n;
	cin >> n;
	vector<array<ll, 3>> in(n);
	for (auto& v : in) for (ll& x : v) cin >> x;
	for (auto [x1, y1, h1] : in) {
		ll r = h1;
		for (auto [x2, y2, h2] : in) {
			if (h2 > h1) r = min<ll>(r, hypot(x1 - x2, y1 - y2));
		}
		cout << r << endl;
	}
}
