#include <bits/stdc++.h>
using namespace std;

#define all(x) begin(x), end(x)
#define sz(x) (ll)(x).size()

using ll = long long;
using ld = long double;

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);

	ll n, m, x, y;
	cin >> n >> m >> x >> y;
	vector<ll> a(n), b(m);
	for (ll& z : a) cin >> z;
	for (ll& z : b) cin >> z;
	sort(all(a));
	sort(all(b));
	ll book = 0;
	ll res = 0;
	for (ll rack = 0; rack < n; rack++) {
		for (ll i = 0; i < y && book < m && b[book] <= a[rack]; i++) book++;
		if (m - book <= (n - rack - 1) * x) {
			res++;
			continue;
		}
		for (ll i = y; i < x && book < m && b[book] <= a[rack]; i++) book++;
		if (m - book > (n - rack - 1) * x) {
			cout << "impossible" << endl;
			return 0;
		}
	}
	cout << res << endl;
}
