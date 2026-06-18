#include <bits/stdc++.h>
using namespace std;

#define all(x) begin(x), end(x)
#define sz(x) (int)(x).size()

using ll = long long;
using ld = long double;
using pt = complex<ld>;

// Kreuzprodukt, 0, falls kollinear.
ld cross(pt a, pt b) {return imag(conj(a) * b);}
ld cross(pt p, pt a, pt b) {return cross(a - p, b - p);}

// Entfernung von Punkt p zur Gearden durch a-b. 2d und 3d
ld distToLine(pt a, pt b, pt p) {
	return abs(cross(p - a, b - a)) / abs(b - a);
}

ll left(pt p) {return real(p) < 0 || (real(p) == 0 && imag(p) < 0);}

void sortAround(pt p, vector<pt>& ps) {
	sort(all(ps), [&](const pt& a, const pt& b){
		if (left(a - p) != left(b - p)) return left(a - p) > left(b - p);
		return cross(p, a, b) > 0;
	});
}

ll gcd(ll a, ll b) {return b == 0 ? a : gcd(b, a % b);}

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);
	vector<pt> dirs;
	for (ll x = 0; x <= 50; x++) {
		for (ll y = 0; y <= 50; y++) {
			if (0 >= x+y) continue;
			if (gcd(x, y) != 1) continue;
			dirs.push_back(pt(x, y));
		}
	}
	sortAround(pt(0, 0), dirs);
	mt19937 rng(time(nullptr));
	ll t;
	cin >> t;
	cout << fixed << setprecision(0);
	for (ll i = 0; i < t; i++) {
		ll j = uniform_int_distribution<ll>(0, sz(dirs) - 2)(rng);
		pt dir1 = dirs[j];
		pt dir2 = dirs[j + 1];
		cout << "? " << dir1.real() << " " << dir1.imag() << endl;
		cout << "? " << dir2.real() << " " << dir2.imag() << endl;

		ld d1, d2;
		cin >> d1 >> d2;
		dir1 /= abs(dir1);
		dir1 *= d1;
		dir2 /= abs(dir2);
		dir2 *= d2;
		ld d = distToLine(dir1, dir2, pt(0, 0));
		cout << "! " << round(d*d*4) << endl;
	}
}
