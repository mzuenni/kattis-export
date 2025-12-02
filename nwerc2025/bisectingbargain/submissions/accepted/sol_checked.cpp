#include <bits/stdc++.h>
using namespace std;

#define all(x) begin(x), end(x)
#define sz(x) (ll)(x).size()

using ll = long long;
using ld = long double;

constexpr ll LIM = 10'001;
constexpr std::array<ll, 9> COINS = {500, 200, 100, 50, 20, 10, 5, 2, 1};

bool splittable(ll x) {
	x %= 2000;
	if (x >= 1000) return false;
	for (ll c : COINS) {
		if (x % c != x % (2 * c)) return false;
		x %= c;
	}
	return true;
}

vector<ll> greedy(ll x, ll lim) {
	vector<ll> res;
	for (ll c : COINS) {
		if (c > lim) continue;
		while (x >= c) {
			res.push_back(c);
			x -= c;
		}
	}
	return res;
}

bool representable(ll k, const std::vector<ll>& coins) {
	std::bitset<LIM> dp;
	dp[0] = 1;
	for (ll c : coins) dp |= dp << c;
	return dp[k];
}

void solve(ll n, const std::vector<ll>& res) {
	if (n % 2 == 0 && representable(n / 2, res)) return;
	// cout << "unsplittable" << endl;
	cout << sz(res) << endl;
	cout << res[0];
	for (ll i = 1; i < sz(res); i++) cout << " " << res[i];
	cout << endl;
	exit(0);
}

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);

	ll n;
	cin >> n;
	solve(n, greedy(n, 500));
	solve(n, greedy(n, 200));
	cout << "splittable" << endl;
}
