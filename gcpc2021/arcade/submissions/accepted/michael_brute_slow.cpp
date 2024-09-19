#include <bits/stdc++.h>
using namespace std;

#define all(x) begin(x), end(x)
#define sz(x) (ll)(x).size()

using ll = long long;
using ld = long double;
using bits = bitset<64>;

map<ll, bool> cache;
bool check(ll l) {
	if (l < 2) return true;
	if (l % 2 == 0) return false;
	if (cache.count(l) == 0)
		cache[l] = check((l-1)/2);
	return cache[l];
}

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);
	ll n;
	cin >> n;
	for (ll i = 0; i < n; i = max(2*i, i+2)) {
		if (check(i-1) && check(n-i-2)) {
			cout << i+1 << endl;
			return 0;
		}
	}
	cout << "impossible" << endl;
}
