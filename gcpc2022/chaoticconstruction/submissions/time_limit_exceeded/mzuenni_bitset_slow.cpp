// reaching a closed segment is weird...
#include <bits/stdc++.h>
using namespace std;

#define all(x) begin(x), end(x)
#define sz(x) (ll)(x).size()

using ll = long long;
using ld = long double;

constexpr ll lim = 200007;
bitset<lim> removed;

ll findNext(ll id) {
	while (!removed[id]) id++;
	return id;
}

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);
	removed[lim - 1] = true;

	ll n, q;
	cin >> n >> q;
	for (ll i = 0; i < q; i++) {
		char type;
		ll a;
		cin >> type >> a;
		if (type == '?') {
			ll b;
			cin >> b;
			if (b < a) swap(a, b);
			if (findNext(a) > b ||	findNext(b) > a+n) {
				cout << "possible\n";
			} else {
				cout << "impossible\n";
			}
		} else {
			removed[a].flip();
			removed[a+n].flip();
		}
	}
}
