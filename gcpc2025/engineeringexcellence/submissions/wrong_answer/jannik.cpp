#include <cmath>
#include <complex>
#include <iomanip>
#include <iostream>
#include <vector>
#include <tuple>

using namespace std;

using ld = long double;
using pt = complex<ld>;
#define x real()
#define y imag()

constexpr ld inf = INFINITY;
constexpr ld eps = 1e-7;

ld sq(ld a) { return a*a; }

ld cross(pt a, pt b) { return (conj(a) * b).y; }
int ccw(pt a, pt b, pt c)
{
	ld t = cross(b - a, c - b);
	return (t < eps) - (t > eps);
}
ld dot(pt a, pt b) { return a.x*b.x + a.y*b.y; }

pt line_intersect(pt a0, pt a1, pt b0, pt b1)
{
	pt d13 = a0 - b0;
	pt d43 = b1 - b0;
	pt d21 = a1 - a0;
	ld un = d43.x * d13.y - d43.y * d13.x;
	ld ud = d43.y * d21.x - d43.x * d21.y;
	if (abs(ud) < eps)
		return pt(inf, inf);
	return pt(a0.x + un * d21.x / ud, a0.y + un * d21.y / ud);
}

pair<pt, pt> line_circle_intersect(pt start, pt d, pt center, ld r)
{
	const auto p = start - center;
	const ld a = sq(d.x) + sq(d.y);
	const ld b = 2*dot(p,d);
	const ld c = sq(p.x) + sq(p.y) - sq(r);

	ld det = sq(b) - 4*a*c;
	if (det < 0)
		return make_pair(pt(inf,inf), pt(inf,inf));
	det = sqrt(det);
	const ld t1 = (-b + det) / (2*a);
	const ld t2 = (-b - det) / (2*a);
	return make_pair(start + t1 * d, start + t2 * d);
}

int main()
{
	int n;
	cin >> n;
	vector<pt> poly(n);
	for (auto& p : poly) {
		ld a, b;
		cin >> a >> b;
		p = pt(a, b);
	}
	ld max_increase = 0;
	for (int i = 0; i < n; i++) {
		const auto a = poly[(i + 1) % n], b = poly[(i + 2) % n], c = poly[(i + 3) % n];
		const auto da = a - poly[i], dc = c - poly[(i + 4) % n];
		if (ccw(a - da, a, c) == 0 or ccw(a, c, c - dc) == 0)
			continue;
		const auto r = abs(a - c) / 2.;
		const auto center = (a + c) * ld(0.5);

		const auto old = abs(a - b) + abs(b - c);

		const auto check = [&](pt p) {
			if (isinf(p.x) or isinf(p.y))
				return;
			max_increase = max(max_increase, abs(a - p) + abs(p - c) - old);
		};

		pt opt = center + pt(0, 1) * (a - c) * ld(0.5); // optimum
		if (ccw(a - da, a, opt) <= 0 and ccw(opt, c, c - dc) <= 0 and dot(da, opt - a) >= -eps and dot(dc, opt - c) >= -eps and ccw(a, c, opt) > 0) // opt is valid

			check(opt);

		if (opt = line_intersect(a, a + da, c, c + dc); abs(opt - center) < r + eps)
			check(opt);
		else {
			auto[p1,p2] = line_circle_intersect(a, da, center, r);
			check(p1), check(p2);
			tie(p1,p2) = line_circle_intersect(c, dc, center, r);
			check(p1), check(p2);
		}
	}

	cout << fixed << setprecision(10) << max_increase << endl;
}
