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


struct big_int {
	static constexpr ll B = 1LL<<31;
	vll dig;
	big_int(ll x = 0) : dig(1,x) {}
	big_int& operator+=(const big_int& rhs) {
		for (ll i = 0, c = 0; i < sz(dig) or i < sz(rhs.dig) or c > 0; i++, c /= B) {
			if (i < sz(rhs.dig)) c += rhs.dig[i];
			if (i < sz(dig)) c += dig[i];
			else dig.resize(i+1);
			dig[i] = c % B;
		}
		return *this;
	}
	bool operator<(const big_int& rhs) const {
		if (sz(dig) != sz(rhs.dig))
			return sz(dig) < sz(rhs.dig);
		for (ll i = sz(dig) - 1; i >= 0; i--)
			if (dig[i] != rhs.dig[i])
				return dig[i] < rhs.dig[i];
		return false;
	}
};

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
			count = std::move(n_c);
		}

	vll order(r+1-l);
	iota(all(order), l);
	sort(all(order), [&](ll l, ll r) { return count[r] < count[l]; });
	for (ll x : order) cout << x << ' ';
	cout << endl;

	return 0;
}
