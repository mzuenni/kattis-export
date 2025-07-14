#include <bits/stdc++.h>
using namespace std;

using ll = int64_t;
using pll = pair<ll, ll>;

#define TS ll ts; cin >> ts; while (ts--)
#define all(x) ::begin(x), ::end(x)
constexpr ll INF = 1e18;

ll n;
vector<ll> xs, ys;

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	
	cin >> n;
	xs.resize(n);
	ys.resize(n);
	for (ll i = 0; i < n; ++i) {
		cin >> xs[i] >> ys[i];
	}

	sort(all(xs));
	sort(all(ys));

	cout << 4 << '\n';
	cout << xs[0] << ' ' << ys[0] << '\n';
	cout << xs[n - 1] << ' ' << ys[0] << '\n';
	cout << xs[n - 1] << ' ' << ys[n - 1] << '\n';
	cout << xs[0] << ' ' << ys[n - 1] << '\n';
	
	return 0;
}
