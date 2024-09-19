#include <bits/stdc++.h>
using namespace std;

#define all(x) begin(x), end(x)
#define sz(x) (ll)(x).size()

using ll = long long;
using ld = long double;

void solve(ll h, ll w, ll hh, ll ww) {
	for (ll i = 0; i < h; i++) {
		for (ll j = 0; j < w; j++) {
			ll k = (i / hh) * (w / ww) + (j / ww);
			cout << (char)('a' + k);//try wrong case
		}
		cout << endl;
	}
	exit(0);
}

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);
	ll h, w, n;
	cin >> h >> w >> n;
	for (ll i = 1; i*i*n <= h*w; i++) {
		ll j = (h*w)/(n*i);
		if (h % i == 0 && w % j == 0 && i*j*n == h*w) solve(h, w, i, j);
		if (w % i == 0 && h % j == 0 && i*j*n == h*w) solve(h, w, j, i);
	}
	cout << "IMPOSSIBLE" << endl;//try wrong case
}
 
