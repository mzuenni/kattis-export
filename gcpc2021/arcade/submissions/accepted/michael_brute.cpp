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
	for (ll i = 0; i < n; i = max(2*i, i+2)) {
		if (__builtin_popcountll(n-1-i) <= 1) {
			cout << i+1 << endl;
			return 0;
		}
	}
	cout << "impossible" << endl;
}
