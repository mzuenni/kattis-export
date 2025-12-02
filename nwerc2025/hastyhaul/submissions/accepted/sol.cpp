#include<vector>
#include<utility>
#include<iostream>
using namespace std;

#define all(x) begin(x), end(x)
#define sz(x) (ll)(x).size()

using ll = long long;
using ull = unsigned long long;
using ld = long double;

constexpr ll N = 64;
 

ull binom[N + 1][N + 1];

// x-ter Knoten auf dem Hamiltonpfad (0-indiziert)
ull ith(ll n, ll k, ull x) {
	if (k == 0) {
		return 0;
	}

	if (x < binom[n - 1][k]) {
		return ith(n - 1, k, x);
	} else {
		x -= binom[n - 1][k];
		return ith(n - 1, k - 1, binom[n - 1][k - 1] - x - 1) | (1ull << (n - 1));
	}
}

// Position der Zahl y auf dem Hamiltonpfad
ull pos(ll n, ll k, ull y) {
	if (k == 0) {
		return 0;
	}

	if ((y & (1ull << (n - 1))) == 0) {
		return pos(n - 1, k, y);
	} else {
		ll inner = pos(n - 1, k - 1, y);
		return binom[n - 1][k - 1] - inner - 1 + binom[n - 1][k];
	}
}

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);

	binom[0][0] = 1;
	for(int i = 0; i <= N; i++) {
		for(int j = 0; j <= N; j++) {
			if (i > 0) {
				binom[i][j] += binom[i - 1][j];
				if (j > 0) {
					binom[i][j] += binom[i - 1][j - 1];
				}
			}
		}
	}

	ll t;
	cin >> t;
	for (ll i = 0; i < t; i++) {
		ll h, w, k;
		cin >> h >> w >> k;
		ull state = 0;
		ll set = 0;
		char c;
		for (ll j = 0; j < w*h; j++) {
			cin >> c;
			state <<= 1;
			if (c != '.') {
				state |= 1;
				set++;
			}
		}
		if ((binom[w*h][set] & 1) != 0) {
			cout << "risky" << endl;
		} else {
			ull goal = ith(w*h, set, pos(w*h, set, state) ^ 1);
			ull pos = goal ^ state;
			std::vector<pair<ll, ll>> ans(2, {-2, -2});
			for (ll j = w*h - 1; j >= 0; j--) {
				if ((pos & 1) != 0) {
					//x,y
					ans[goal & 1] = {(j % w), (j / w) }; 
				}
				pos >>= 1;
				goal >>= 1;
			}
			for (auto [x, y] : ans) cout << y+1 << " " << x+1 << endl;
		}
	}
}
