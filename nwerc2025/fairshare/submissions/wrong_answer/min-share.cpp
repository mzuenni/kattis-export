#include <bits/stdc++.h>
using namespace std;

#define all(x) begin(x), end(x)
#define sz(x) (ll)(x).size()

using ll = long long;
using ld = long double;


int main(int argc, char **argv) {
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);

	ll n;
	cin >> n;
	vector<ll> a(n), b(n);
	ll sumA = 0;
	ll sumB = 0;
	for (ll i = 0; i < n; i++) {
		cin >> a[i] >> b[i];
		sumA += a[i];
		sumB += b[i];
	}
	ll i = distance(b.begin(), min_element(all(b)));
	ll got = sumA - a[i];
	ll open = sumB - got;
	if (open > b[i]) {
		cout << "impossible" << endl;
	} else {
		cout << i+1 << endl;
	}
}
