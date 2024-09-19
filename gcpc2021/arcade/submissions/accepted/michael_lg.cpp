#include <bits/stdc++.h>
using namespace std;

#define all(x) begin(x), end(x)
#define sz(x) (ll)(x).size()

using ll = long long;
using ld = long double;

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);
	ll n;
	cin >> n;
	ll res = (1ll << __lg(n)) | 1;
	if (__builtin_popcountll(n - res) <= 1) {
		cout << res << endl;
	} else {
		cout << "impossible" << endl;
	}
}
