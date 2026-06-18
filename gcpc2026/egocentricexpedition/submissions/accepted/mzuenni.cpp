#include <bits/stdc++.h>
using namespace std;

#define all(x) begin(x), end(x)
#define sz(x) (int)(x).size()

using ll = long long;
using ld = long double;
using pt = complex<ld>;

// Kreuzprodukt, 0, falls kollinear.
ld cross(pt a, pt b) {return imag(conj(a) * b);}

// Entfernung von Punkt p zur Gearden durch a-b. 2d und 3d
ld distToLine(pt a, pt b, pt p) {
	return abs(cross(p - a, b - a)) / abs(b - a);
}

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);
	ll t;
	cin >> t;
	cout << fixed << setprecision(0);
	for (ll i = 0; i < t; i++) {
		cout << "? 1 0\n? 1 1" << endl;
		ld d1, d2;
		cin >> d1 >> d2;
		d2 /= sqrt(2.0l);
		ld d = distToLine(pt(d1, 0), pt(d2, d2), pt(0, 0));
		cout << "! " << round(d*d*4) << endl;
	}
}

