#include <bits/stdc++.h>
using namespace std;

#define all(x) begin(x), end(x)
#define sz(x) (ll)(x).size()

using ll = long long;
using ld = long double;
using pt = complex<double>;

// Kreuzprodukt, 0, falls kollinear.
double cross(pt a, pt b) {return imag(conj(a) * b);}
double cross(pt p, pt a, pt b) {return cross(a - p, b - p);}

pt readPt() {
	ll x, y;
	cin >> x >> y;
	return {x, y};
}

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);
	deque<pt> lower, upper, path;
	lower = upper = path = {readPt()};
	pt e = readPt();
	ll n;
	cin >> n;

	auto add = [&](pt l, pt u) {
		//convex hull, andrews algorithm
		while (sz(lower) > 1 && cross(lower.end()[-2], lower.end()[-1], l) >= 0) lower.pop_back();
		lower.push_back(l);
		while (sz(upper) > 1 && cross(upper.end()[-2], upper.end()[-1], u) <= 0) upper.pop_back();
		upper.push_back(u);

		while (sz(lower) > 1 && 
			   sz(upper) > 1 &&
			   cross(lower[0], lower[1], upper[1]) <= 0) {
			lower.pop_front();
			upper.pop_front();
			if (lower[0].real() < upper[0].real()) {
				upper.push_front(lower[0]);
			} else if (lower[0].real() > upper[0].real()) {
				lower.push_front(upper[0]);
			}
			if (path.size() > 1 && cross(path.end()[-2], path.end()[-1], upper[0]) == 0) {
				path.pop_back(); //remove colinear points on path...
			}
			path.push_back(upper[0]);
		}
	};

	for (ll i = 0; i < n; i++) {
		ll x, y1, y2;
		cin >> x >> y1 >> y2;
		add({x, y1}, {x, y2});
	}
	add(e, e);
	//path.push_back(e);
	for (auto e : path) {
		cout << (ll)round(e.real()) << " " << (ll)round(e.imag()) << endl;
	}

}
