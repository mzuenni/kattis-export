#include <bits/stdc++.h>
using namespace std;

using ll = int64_t;
using pll = pair<ll, ll>;

#define TS ll ts; cin >> ts; while (ts--)
#define all(x) ::begin(x), ::end(x)
constexpr ll INF = 1e18;

ll n, d;
vector<vector<ll>> a;

bool test(vector<ll>& xs) {
	cerr << "test" << endl;
	ll fp = 0;
	ll len = xs.size();
	ll start = 0;
	while (fp < len) {
		if (xs[fp] < start) return false;

		ll bp = fp;
		while (bp < len && xs[bp] < xs[fp] + d) ++bp;

		start = max(start + 2 * d, xs[bp - 1] + d + 1);
		fp = bp;
	}
	return true;
}

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	
	cin >> n >> d;
	a.resize(n);
	for (ll i = 0; i < n; ++i) {
		ll x;
		cin >> x;
		a[x].push_back(i);
	}

	for (ll i = 0; i < n + 1; ++i) {
		if (test(a[i])) {
			cout << i << '\n';
			break;
		}
	}
	
	return 0;
}
