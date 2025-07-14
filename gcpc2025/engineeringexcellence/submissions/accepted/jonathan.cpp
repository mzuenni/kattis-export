#include <bits/stdc++.h>
using namespace std;

using ll = int64_t;
using pll = pair<ll, ll>;
using ld = long double;
using pt = complex<ld>;

#define TS ll ts; cin >> ts; while (ts--)
#define all(x) ::begin(x), ::end(x)
constexpr ll INF = 1e18;
const ld EPS = 1e-9;

ld cross(pt a, pt b) { return imag(conj(a) * b); }
ld cross(pt p, pt a, pt b) { return cross(a - p, b - p); }
ld dot(pt a, pt b) { return real(conj(a) * b); }
ld dot(pt p, pt a, pt b) { return dot(a - p, b - p); }

vector<pt> circle_ray_intersection(pt center, ld r, pt orig, pt dir) {
	vector<pt> result;
	ld a = norm(dir);
	ld b = 2 * dot(dir, orig - center);
	ld c = norm(orig - center) - r * r;
	ld discr = b * b - 4 * a * c;
	if (discr >= 0) {
		ld t1 = -(b + sqrt(discr)) / (2 * a);
		ld t2 = -(b - sqrt(discr)) / (2 * a);
		if (t1 >= 0) result.push_back(t1 * dir + orig);
		if (t2 >= 0 && abs(t1 - t2) > EPS) {
			result.push_back(t2 * dir + orig);
		}
	}
	return result;
}

pt line_intersection(pt a, pt b, pt c, pt d) {
	ld x = cross(b - a, d - c);
	ld y = cross(c - a, d - c);
	return a + (y / x) * (b - a);
}

ll n;
vector<pt> a;

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	
	cin >> n;
	a.resize(n);
	for (ll i = 0; i < n; ++i) {
		ll x, y;
		cin >> x >> y;
		a[i] = { (ld)x, (ld)y };
	}
	for (ll i = 0; i < 4; ++i) {
		a.push_back(a[i]);
	}

	ld res = 0.0;
	for (ll i = 0; i < n; ++i) {
		ld cur = abs(a[i + 2] - a[i + 1]) + abs(a[i + 2] - a[i + 3]);
		pt center = a[i + 1] + pt{ 0.5, 0 } * (a[i + 3] - a[i + 1]);
		ld radius = 0.5 * abs(a[i + 3] - a[i + 1]);

		vector<pt> candidates;
		candidates.push_back(center + pt{ 0, -0.5 } * (a[i + 3] - a[i + 1]));
		//for (pt p : circle_ray_intersection(center, radius, a[i + 2], a[i + 2] - a[i + 1])) candidates.push_back(p);
		//for (pt p : circle_ray_intersection(center, radius, a[i + 2], a[i + 2] - a[i + 3])) candidates.push_back(p);
		for (pt p : circle_ray_intersection(center, radius, a[i + 1], a[i + 1] - a[i + 0])) candidates.push_back(p);
		for (pt p : circle_ray_intersection(center, radius, a[i + 3], a[i + 3] - a[i + 4])) candidates.push_back(p);
		for (pt p : circle_ray_intersection(center, radius, a[i + 1], pt{ 0, 1 } * (a[i + 1] - a[i + 0]))) candidates.push_back(p);
		for (pt p : circle_ray_intersection(center, radius, a[i + 3], pt{ 0, -1 } * (a[i + 3] - a[i + 4]))) candidates.push_back(p);
		if (abs(cross(a[i + 0] - a[i + 1], a[i + 3] - a[i + 4])) >= EPS) {
			candidates.push_back(line_intersection(a[i + 0], a[i + 1], a[i + 3], a[i + 4]));
		}

		for (pt p : candidates) {
			if (
				cross(a[i + 0], a[i + 1], p) >= -EPS &&
				cross(a[i + 1], p, a[i + 3]) >= -EPS &&
				cross(p, a[i + 3], a[i + 4]) >= -EPS &&
				dot(a[i + 1], p, a[i + 0]) <= EPS &&
				dot(a[i + 3], p, a[i + 4]) <= EPS &&
				abs(center - p) <= radius + EPS
			) {
				res = max(res, abs(p - a[i + 1]) + abs(p - a[i + 3]) - cur);
			}
		}
	}
	cout << setprecision(16) << fixed << res << '\n';
	
	return 0;
}
