#include <iostream>
#include <vector>
#include <array>
#include <algorithm>
#include <numeric>

using namespace std;
using ll = long long;
using vll = vector<ll>;

#define sz(a) ((ll)(a).size())
#define all(a) (a).begin(),(a).end()


using big_int = __uint128_t;

constexpr ll n = 5;
const array<ll, n> vals{{4,6,8,12,20}};

int main() {
	vll cnt(n);
	for (ll&x : cnt) cin >> x;
	ll r = 0, l = 0;
	for (ll i = 0; i < n; i++)
		r += vals[i] * cnt[i], l += cnt[i];

	vector<big_int> count(r+1);
	count[0] = 1;
	for (ll i = 0; i < n; i++)
		while (cnt[i]-- > 0) {
			vector<big_int> n_c(r+1);
			for (ll x = 0; x + vals[i] <= r; x++)
				for (ll v = 1; v <= vals[i]; v++)
					n_c[x + v] += count[x];
			count = move(n_c);
		}

	vll order(r+1-l);
	iota(all(order), l);
	sort(all(order), [&](ll l, ll r) { return count[r] < count[l]; });
	for (ll x : order) cout << x << ' ';
	cout << endl;

	return 0;
}
