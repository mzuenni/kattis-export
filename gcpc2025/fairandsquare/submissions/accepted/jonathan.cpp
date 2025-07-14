#include <bits/stdc++.h>
using namespace std;

using ll = int64_t;
using pll = pair<ll, ll>;

#define TS ll ts; cin >> ts; while (ts--)
#define all(x) ::begin(x), ::end(x)
constexpr ll INF = 1e18;

ll n, m;
vector<vector<bool>> a;
vector<pll> b;

bool test(ll s) {
	vector<vector<ll>> f(n, vector<ll>(m));
	for (auto [x, y] : b) {
		if (f[x][y]) continue;

		for (ll dx = 0; dx < s; ++dx)
		for (ll dy = 0; dy < s; ++dy) {
			if (x + dx >= n) return false;
			if (y + dy >= m) return false;
			if (!a[x + dx][y + dy]) return false;
			if (f[x + dx][y + dy]) return false;

			f[x + dx][y + dy] = true;
		}
	}

	return true;
}

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	
	cin >> n >> m;
	a.resize(n);
	for (ll i = 0; i < n; ++i) {
		a[i].resize(m, false);
		for (ll j = 0; j < m; ++j) {
			char c;
			cin >> c;
			if (c == '#') {
				a[i][j] = true;
				b.push_back({ i, j });
			}
		}
	}

	ll res = 1;
	for (ll i = 2; i <= min(n, m); ++i) {
		if (b.size() % (i * i) != 0) continue;
		if (!test(i)) continue;
		res = i;
	}
	cout << res << '\n';
	
	return 0;
}
