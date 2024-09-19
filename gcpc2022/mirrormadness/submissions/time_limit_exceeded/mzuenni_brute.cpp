#include <bits/stdc++.h>
using namespace std;

#define all(x) begin(x), end(x)
#define sz(x) (ll)(x).size()

using ll = long long;
using ld = long double;
using pt = complex<ll>;

pt readPT() {
	ll x, y;
	cin >> x >> y;
	return pt(x, y);
}

// Kreuzprodukt, 0, falls kollinear.
ll cross(pt a, pt b) {return imag(conj(a) * b);}
ll cross(pt p, pt a, pt b) {return cross(a - p, b - p);}

// -1 => gegen den Uhrzeigersinn
//  0 => kolliniear
//  1 => im Uhrzeigersinn.
ll orientation(pt a, pt b, pt c) {
	ll orien = cross(b - a, c - a);
	return (orien > 0) - (orien < 0);
}

constexpr ll inf = 0x3FFFFFFF;

ll len(pt a) {
	return abs(real(a)) + abs(imag(a));
}

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);

	ll n, m; // number of corners of the polygon and number of points to print
	cin >> n >> m;

	vector<pt> in(n);
	for (ll i = 0; i < n; i++) in[i] = readPT();
	in.push_back(in[0]);

	pt s = readPT(); // start point must be on polygon and not a corner | could always be (0,0)
	pt d(1,1);

	for (ll i = 0; i < m; i++) {
		ll steps = inf;
		pt nextDir = d;
		for (ll j = 0; j < n; j++) {
			if (orientation(s, s+d, in[j]) * orientation(s, s+d, in[j+1]) <= 0) {
				ll curSteps;
				pt curDir;
				if (real(in[j]) == real(in[j+1])) {
					curSteps = (real(in[j]) - real(s)) * real(d);
					curDir = {-real(d), imag(d)};
				} else {
					curSteps = (imag(in[j]) - imag(s)) * imag(d);
					curDir = {real(d), -imag(d)};
				}
				if (curSteps > 0 && curSteps < steps) {
					steps = curSteps;
					nextDir = curDir;
				}
			}
		}
		s += d*steps;
		d = nextDir;
		cout << real(s) << " " << imag(s) << endl;
	}
}
