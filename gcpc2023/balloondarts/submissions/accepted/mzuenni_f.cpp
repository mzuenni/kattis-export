// if we have at most k lines to cover all points
// we can choose k+1 points and among them a pair
// has to belong to the same line
#include <bits/stdc++.h>
using namespace std;

#define all(x) begin(x), end(x)
#define sz(x) (ll)(x).size()

using ll = long long;
using ld = long double;
using pt = complex<ll>;

constexpr ll tries[4] = {0, 1, 4*5, 9*5};

mt19937 rng(123456789);
ll random(ll l, ll r) {
	return uniform_int_distribution<ll>(l, r-1)(rng);
}

// Kreuzprodukt, 0, falls kollinear.
ll cross(pt a, pt b) {return imag(conj(a) * b);}
ll cross(pt p, pt a, pt b) {return cross(a - p, b - p);}

vector<pt> remaining(const vector<pt>& todo, pt a, pt b) {
	vector<pt> res;
	for (pt x : todo) {
		if (cross(a, b, x) != 0) {
			res.push_back(x);
		}
	}
	return res;
}

bool solve(const vector<pt>& todo, ll depth = 3) {
	if (sz(todo) <= 2*depth) return true;
	if (depth == 1) {
		return remaining(todo, todo[0], todo[1]).empty();
	} else {
		for (ll i = 0; i <= depth; i++) {
			for (ll j = 0; j < i; j++) {
				if (solve(remaining(todo, todo[i], todo[j]), depth - 1)) return true;
			}
		}
		return false;
	}
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
	mt19937 rng(123456789);//unnecessary
	shuffle(all(in), rng);
	if (solve(in)) {
		cout << "possible" << endl;
	} else {
		cout << "impossible" << endl;
	}
}
