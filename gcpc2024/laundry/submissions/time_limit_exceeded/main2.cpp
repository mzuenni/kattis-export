#include <bits/stdc++.h>
using namespace std;

#define all(x) begin(x), end(x)
#define sz(x) (ll)(x).size()

using ll = long long;
using ld = long double;

constexpr ll lim = 3;
constexpr ll COMB = (1ll << lim) - 1;
using arr = std::array<ll, COMB+1>;

void solve() {
	ll k;
	cin >> k;
	arr in{};
	cin >> in[1] >> in[2] >> in[4] >> in[3] >> in[6] >> in[5] >> in[7];

	arr req{};
	ll rsum = 0;
	for (ll i = 1; i <= COMB; i++) {
		req[i] = max<ll>(0, (in[i] + k - 1) / k + 1 - (1ll << bitset<64>(i).count()));//?
		rsum += req[i];
	}
 
	for (ll extra = 0;; extra++) {
		for (ll da = 0; da <= extra; da++) {
			for (ll db = 0; da+db <= extra; db++) {
				ll dc = extra-da-db;

				bool ok = true;
				for (ll mask = 1; mask < (1ll << COMB) && ok; mask++) {//mask of vertices left
					ll l = 0;
					ll r = 0;

					arr tmp = req;
					tmp[1] += da;
					tmp[2] += db;
					tmp[4] += dc;
					for (ll i = 1; i <= COMB; i++) {//enumerate vertices left
						if (((2*mask) & (1ll << i)) != 0) {//enumerate vertices in mask
							l += in[i];//value left

							for (ll j = 1; j <= COMB; j++) {//enumerate vertices right
								if ((i&j) == j) {//enumerate neighbourhood
									r += tmp[j];
									tmp[j] = 0;
								}
							}
						}
					}
					ok = l <= r*k;
				}

				if (ok) {
					cout << rsum+extra << endl;
					return; 
				}
			}
		}
	}
}

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);

	ll t; 
	cin >> t; 
	while (t--) {
		solve(); 
	}
}
