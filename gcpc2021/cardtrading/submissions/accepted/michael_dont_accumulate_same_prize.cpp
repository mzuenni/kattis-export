#include <bits/stdc++.h>
using namespace std;

#define all(x) begin(x), end(x)
#define sz(x) (ll)(x).size()

using ll = long long;
using ld = long double;

constexpr ll lim = 10000*100;

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);
	ll n;
	cin >> n;
	vector<ll> buy(lim), sell(lim);
	ll buyers = 0;
	for (ll i = 0; i < n; i++) {
		ld p;
		ll b, s;
		cin >> p >> b >> s;
		ll j = round(p*100);
		buy[j] = b;
		sell[j] = s;
		buyers += b;
	}
	ll res = 0;
	ll prize = -1;
	ll sellers = 0;
	for (ll i = 0; i < lim; i++) {
		sellers += sell[i];
		ll curRes = i*min(sellers, buyers);
		if (curRes > res) {
			res = curRes;
			prize = i;
		}
		buyers -= buy[i];
	}
	if (prize < 0) {
		cout << "impossible" << endl;
	} else {
		cout << fixed << setprecision(2) << prize/100.0l << " " << res/100.0l << endl;
	}
}
