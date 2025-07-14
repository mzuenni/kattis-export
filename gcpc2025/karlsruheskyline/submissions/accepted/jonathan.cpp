#include <bits/stdc++.h>
using namespace std;

using ll = int64_t;
using pll = pair<ll, ll>;

#define TS ll ts; cin >> ts; while (ts--)
#define all(x) ::begin(x), ::end(x)
constexpr ll INF = 1e18;

ll n, l, r;

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	
	cin >> n >> l >> r;
	if (l + r == 2 || l + r > n + 1) {
		cout << "no\n";
	}
	else {
		cout << "yes\n";
		vector<ll> res(n, -1);

		bool rev = false;
		if (r == 1) {
			swap(l, r);
			rev = true;
		}

		for (ll i = 0; i < l; ++i) res[l - (i + 1)] = n - (i + 1);
		for (ll i = 0; i < r - 1; ++i) res[n - r + 1 + i] = n - (l + i + 1);
		for (ll i = 0; i < n - (l + r - 1); ++i) res[l + i] = i;

		if (rev) reverse(all(res));
		for (ll x : res) cout << (x + 1) << ' ';
		cout << '\n';
	}
	
	return 0;
}
