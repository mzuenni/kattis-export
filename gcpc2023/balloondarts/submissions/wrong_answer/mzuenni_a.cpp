#include <bits/stdc++.h>
using namespace std;

#define all(x) begin(x), end(x)
#define sz(x) (ll)(x).size()

using ll = long long;
using ld = long double;
using pt = complex<ll>;

mt19937 rng(123456789);
ll random(ll l, ll r) {
	return uniform_int_distribution<ll>(l, r-1)(rng);
}

// Kreuzprodukt, 0, falls kollinear.
ll cross(pt a, pt b) {return imag(conj(a) * b);}
ll cross(pt p, pt a, pt b) {return cross(a - p, b - p);}


bool solve(const vector<pt>& todo) {
	if (sz(todo) <= 6) return true;
	for (ll i = 0; i < 5000; i++) {
		vector<ll> ps;
		while (sz(ps) < 6) {
			ll c = random(0, sz(todo));
			bool ok = true;
			for (ll x : ps) ok &= x != c;
			if (ok) ps.push_back(c);
		}
		bool ok = true;
		for (ll i = 0; i < sz(todo) && ok; i++) {
			ok = cross(todo[ps[0]], todo[ps[1]], todo[i]) == 0 ||
				 cross(todo[ps[2]], todo[ps[3]], todo[i]) == 0 ||
				 cross(todo[ps[4]], todo[ps[5]], todo[i]) == 0;
		}
		if (ok) return true;
	}
	return false;
}

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);
	ll n;
	cin >> n;
	vector<pt> in(n);
	for (ll i = 0; i < n; i++) {
		ll x, y;
		cin >> x >> y;
		in[i] = {x, y};
	}
	if (solve(in)) {
		cout << "possible" << endl;
	} else {
		cout << "impossible" << endl;
	}
}
