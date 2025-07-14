#include <bits/stdc++.h>
using namespace std;

#define all(x) begin(x), end(x)
#define sz(x) (ll)(x).size()

using ll = long long;
using ld = long double;
using pt = complex<ld>;

constexpr ld EPS = 1e-9;	//no idea if this works...

// Skalarprodukt.
auto dot(pt a, pt b) {return real(conj(a) * b);}

// Kreuzprodukt, 0, falls kollinear.
auto cross(pt a, pt b) {return imag(conj(a) * b);}
auto cross(pt p, pt a, pt b) {return cross(a - p, b - p);}


pt lineIntersection(pt a, pt b, pt c, pt d) {
	auto x = cross(b - a, d - c);
	auto y = cross(c - a, d - c);
	return a + y/x*(b - a);
}

pt circleRayIntersection(pt center, ld r2, pt orig, pt dir) {
	vector<pt> result;
	ld a = norm(dir);
	ld b = 2 * dot(dir, orig - center);
	ld c = norm(orig - center) - r2;
	ld discr = b * b - 4 * a * c;
	ld t1 = -(b + sqrt(discr)) / (2 * a);
	ld t2 = -(b - sqrt(discr)) / (2 * a);
	return max(t1, t2) * dir + orig;
}

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);

	ll n;
	cin >> n;
	vector<pt> in(n);
	for (auto& p : in) {
		ld x, y;
		cin >> x >> y;
		p = {2*x, 2*y};
	}

	for (ll i : {0,1,2,3}) in.push_back(in[i]);

	ld best = 0;
	for (ll i = 0; i < n; i++) {
		pt a = in[i+0];
		pt b = in[i+1];
		pt c = in[i+2];// <- move this
		pt d = in[i+3];
		pt e = in[i+4];

		pt mid = (b + d) / pt(2, 0);
		ld rad2 = norm(mid-b);
		

		auto test = [&](pt p){
			if (dot(b-p, d-p) <= EPS		// angle at p >= 90° (alternative: norm(p-mid) <= rad2 + EPS)
				&& cross(p,b,d) <= EPS 		// angle at p <= 180°
				&& cross(p,a,b) >= -EPS		// a,b,p <= 180°
				&& cross(p,d,e) >= -EPS		// p,d,e <= 180°
				&& dot(p-b, a-b) <= EPS		// angle at b >= 90°
				&& dot(p-d, e-d) <= EPS		// angle at d >= 90°
				) {
				best = max(best, abs(b-p) + abs(p-d) - abs(b-c) - abs(c-d));
			}
		};

		if (cross(b-a, d-e) < 0) test(lineIntersection(a, b, d, e));//can be parallel
		test(mid + (b-mid) * pt(0, 1));
		test(circleRayIntersection(mid, rad2, b, (b-a)*pt(0, 1)));
		test(circleRayIntersection(mid, rad2, d, (d-e)*pt(0,-1)));
	}

	cout << fixed << setprecision(10) << best*0.5 << endl;
}
