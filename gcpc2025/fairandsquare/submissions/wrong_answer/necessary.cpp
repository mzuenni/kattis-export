#include <bits/stdc++.h>
using namespace std;

#define all(x) begin(x), end(x)
#define sz(x) (ll)(x).size()

using ll = long long;
using ld = long double;

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);

	ll h, w;
	cin >> h >> w;
	w += 2;
	h += 2;
	vector<string> in(h);
	in[0] = string(w, '.');
	in[h-1] = string(w, '.');
	for (ll i = 1; i + 1 < h; i++) cin >> in[i], in[i] = "." + in[i] + ".";

	ll sum = 0;
	ll ans = 0;
	for (ll i = 0; i < h; i++) {
		ll cur = 0;
		for (ll j = 0; j < w; j++) {
			if (in[i][j] == '#') cur++, sum++;
			else {
				ans = gcd(ans, cur);
				cur = 0;
			}
		}
	}
	for (ll j = 0; j < w; j++) {
		ll cur = 0;
		for (ll i = 0; i < h; i++) {
			if (in[i][j] == '#') cur++;
			else {
				ans = gcd(ans, cur);
				cur = 0;
			}
		}
	}

	for (ll i = sum; i > 0; i--) {
		if (sum % (i*i) == 0) {
			ans = gcd(ans, i);
			break;
		}
	}
	cout << ans << endl;
}
