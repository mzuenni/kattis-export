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

bool solve(const vector<pt>& todo) {
	if (sz(todo) <= 6) return true;
	bitset<10007> used;
	for (ll i = 0; i < 1000000; i++) {
		vector<ll> selected;
		while (sz(selected) < 7) {
			ll x = random(0, sz(todo));
			if (!used[x]) {
				used[x] = true;
				selected.push_back(x);
			}
		}
		sort(all(selected));
		vector<pt> test;
		for (ll x : selected) {
			test.push_back(todo[x]);
			used[x] = false;
		}
		if (sz(convexHull(test)) > 6) return false;
	}
	return true;
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
