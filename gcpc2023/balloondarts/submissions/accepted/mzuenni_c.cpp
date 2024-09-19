// in the case of two lines one goes through two points of the convex hull
// => only the first line needs to be sampled
// => faster
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

bool solveLine(const vector<pt>& todo) {
	if (sz(todo) <= 2) return true;
	return remaining(todo, todo[0], todo[1]).empty();
}

vector<pt> convexHull(const vector<pt>& p){
	int k = 0;
	vector<pt> h(2 * sz(p));
	for (int i = 0; i < sz(p); i++) {// Untere Hülle.
		while (k > 1 && cross(h[k-2], h[k-1], p[i]) <= 0) k--;
		h[k++] = p[i];
	}
	for (int i = sz(p)-2, t = k; i >= 0; i--) {// Obere Hülle.
		while (k > t && cross(h[k-2], h[k-1], p[i]) <= 0) k--;
		h[k++] = p[i];
	}
	h.resize(k);
	if (sz(h) > 1) h.pop_back();
	return h;
}


bool solve2Line(const vector<pt>& todo) {
	vector<pt> h = convexHull(todo);
	if (sz(h) <= 2) return true;
	if (sz(h) > 4) return false;
	for (ll i = 0; i < sz(h); i++) {
		for (ll j = 0; j < i; j++) {
			if (solveLine(remaining(todo, h[i], h[j]))) return true;
		}
	}
	return false;
}


bool solve(const vector<pt>& todo) {
	if (sz(todo) <= 6) return true;
	for (ll i = 0; i < 90; i++) {
		ll j = random(0, sz(todo));
		ll k = j;
		while (k == j) k = random(0, sz(todo));
		if (solve2Line(remaining(todo, todo[j], todo[k]))) return true;
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

	sort(in.begin(), in.end(), [](const pt& a, const pt& b){
		return real(a) == real(b) ? imag(a) < imag(b) : real(a) < real(b);
	});
	in.erase(unique(in.begin(), in.end()), in.end());

	if (solve(in)) {
		cout << "possible" << endl;
	} else {
		cout << "impossible" << endl;
	}
}
