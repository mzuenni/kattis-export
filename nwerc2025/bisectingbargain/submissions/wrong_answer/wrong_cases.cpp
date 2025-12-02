#include <bits/stdc++.h>
using namespace std;

#define all(x) begin(x), end(x)
#define sz(x) (ll)(x).size()

using ll = long long;
using ld = long double;

constexpr std::array<ll, 9> COINS = {500, 200, 100, 50, 20, 10, 5, 2, 1};

bool splittable(ll x) {
	x %= 1000;
	if (x ==   0) return true;
	if (x ==   4) return true;
	if (x ==  40) return true;
	if (x ==  44) return true;
	if (x == 400) return true;
	if (x == 404) return true;
	if (x == 440) return true;
	if (x == 444) return true;
	return false;
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

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);

	ll n;
	cin >> n;
	if (!splittable(n)) {
		// cout << "unsplittable" << endl;
		vector<ll> res;
		if (n >= 1000 && splittable(n-1000)) {
			res = greedy(n, 200);
		} else {
			res = greedy(n, 500);
		}
		cout << sz(res) << endl;
		cout << res[0];
		for (ll i = 1; i < sz(res); i++) cout << " " << res[i];
		cout << endl;
	} else {
		cout << "splittable" << endl;
	}
}
