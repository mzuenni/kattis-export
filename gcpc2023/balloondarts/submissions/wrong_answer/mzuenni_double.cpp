#include <bits/stdc++.h>
using namespace std;

#define all(x) begin(x), end(x)
#define sz(x) (ll)(x).size()

using ll = long long;
using ld = double;
using pt = complex<ld>;

constexpr ld eps = 1e-6; 
constexpr ll tries[4] = {0, 1, 4*5, 9*5};

mt19937 rng(123456789);
ll random(ll l, ll r) {
	return uniform_int_distribution<ll>(l, r-1)(rng);
}

// Kreuzprodukt, 0, falls kollinear.
ll cross(pt a, pt b) {return imag(conj(a) * b);}
ll cross(pt p, pt a, pt b) {return cross(a - p, b - p);}


bool solve(const vector<pt>& todo, ll depth = 3) {
	if (sz(todo) <= 2*depth) return true;
	for (ll i = 0; i < tries[depth]; i++) {
		ll j = random(0, sz(todo));
		ll k = j;
		while (k == j) k = random(0, sz(todo));
		vector<pt> remain;
		for (pt c : todo) {
			if (abs(cross(todo[j], todo[k], c)) >= eps) remain.push_back(c);
		}
		if (solve(remain, depth - 1)) return true;
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
