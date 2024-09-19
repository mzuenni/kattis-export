// lets name the first line k the second k-1 etc.
// if there are less than k^2 points try all pairs					=> k^2 * (T(k-1) + n)
// else there must be a line which contains k+1 points and this
// must be part of a solution if a solution exists. If we try any
// k^2 points at least one has to lie on a line with k+1 points.
// For each of the k^2 points  that we try we can search for the
// required line by sorting all other points around this point
// and check if there are enough points in one direction			=> k^2 * (T(k-1) + nlog(n))
#include <bits/stdc++.h>
using namespace std;

#define all(x) begin(x), end(x)
#define sz(x) (ll)(x).size()

using ll = long long;
using ld = long double;
using pt = complex<ll>;

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

//runtime: T(n,d) = d^2 * (nlog(n) + T(n,d-1))
bool solve(const vector<pt>& todo, ll depth = 3) {
	if (sz(todo) <= 2*depth) return true;
	if (depth == 0) return false;
	if (sz(todo) <= depth*depth) {
		for (ll i = 0; i < sz(todo); i++) {
			for (ll j = 0; j < i; j++) {
				if (solve(remaining(todo, todo[i], todo[j]), depth - 1)) return true;
			}
		}
		return false;
	} else {
		for (ll i = 0; i <= depth*(depth-1); i++) {
			vector<pt> other;
			for (ll j = 0; j < sz(todo); j++) {
				if (i != j) {
					pt cur = todo[j] - todo[i];
					if (cur.real() < 0 || (cur.real() == 0 && cur.imag() < 0)) cur = -cur;
					other.push_back(cur);
				}
			}
			sort(all(other), [](const pt& a, const pt& b){return cross(a, b) > 0;});
			for (ll j = 0; j < sz(other);) {
				ll k = j+1;
				while (k < sz(other) && cross(other[j], other[k]) == 0) k++;
				if (k-j >= depth) return solve(remaining(todo, todo[i], todo[i] + other[j]), depth - 1);
				j=k;
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
	if (solve(in)) {
		cout << "possible" << endl;
	} else {
		cout << "impossible" << endl;
	}
}
