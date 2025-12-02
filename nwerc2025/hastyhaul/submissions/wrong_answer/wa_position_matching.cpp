#include <bits/stdc++.h>
using namespace std;

#define all(x) begin(x), end(x)
#define sz(x) (ll)(x).size()

using ll = long long;
using ld = long double;

bool possible(ll n, ll k){
	return (n & k) != k;
}

mt19937 rng(123456789);
// for odd n one posiiton is unmatched (-1)
vector<ll> randomMatching(ll n) {
	vector<ll> res(n, -1);
	vector<ll> perm(n);
	iota(all(perm), 0);
	shuffle(all(perm), rng);
	for (ll i = 1; i < n; i += 2) {
		res[perm[i]] = perm[i-1];
		res[perm[i-1]] = perm[i];
	}
	return res;
}



int main(int argc, char **argv) {
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);

	vector<vector<ll>> positionsMatching(65);

	for (ll i = 0; i < sz(positionsMatching); i++) positionsMatching[i] = randomMatching(i);

	ll t;
	cin >> t;
	for (ll i = 0; i < t; i++) {
		ll h, w, k;
		cin >> h >> w >> k;
		bitset<64> state;
		for (ll y = 0; y < h; y++) {
			for (ll x = 0; x < w; x++) {
				char c;
				cin >> c;
				if (c == '#') state[y * w + x] = true;
			}
		}
		if (possible(w*h, state.count())) {
			ll a = -1;
			ll b = -1;
			for (ll i = 0; i < w*h && a < 0; i++) {
				ll j = positionsMatching[w*h][i];
				if (j < 0) continue;
				if (state[i] != state[j]) {
					a = i;
					b = j;
					if (state[b]) swap(a, b);
				}
			}
			if (a < 0) {
				cout << "RiSkY" << endl;
			} else {
				cout << (a / w)+1 << " " << (a % w)+1 << endl;
				cout << (b / w)+1 << " " << (b % w)+1 << endl;
			}
		} else {
			cout << "risky" << endl;
		}
	}
}
