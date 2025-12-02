#include <bits/stdc++.h>
using namespace std;

#define all(x) begin(x), end(x)
#define sz(x) (ll)(x).size()

using ll = long long;
using ld = long double;

int main(int argc, char **argv) {
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);

	ll n;
	cin >> n;
	vector<ll> in(n);
	for (ll& x : in) cin >> x, x--;

	vector<pair<ll, ll>> res;
	auto move = [&](ll i, ll j) {
		if (i == j) return;
		res.emplace_back(i, j);
		vector<ll> window(in.begin() + i, in.begin() + i + 3);
		in.erase(in.begin() + i, in.begin() + i + 3);
		in.insert(in.begin() + j, all(window));
	};

	mt19937 rng(123456789);
	uniform_int_distribution<ll> dist(0, 2);

	do {
		for (ll i = n-1; i >= 3; i--) {
			ll pos = 0;
			while (in[pos] != i) pos++;
			if (pos < 2) move(0, 2 - pos), pos = 2;
			move(pos - 2, i - 2);
		}
		if (in[0] == 0 && in[1] == 1 && in[2] == 2) break;
		move(dist(rng), dist(rng));
	} while(true);

	cout << sz(res) << endl;
	for (auto [a, b] : res) cout << a+1 << " " << b+1 << endl;
}
