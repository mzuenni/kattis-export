#include <bits/stdc++.h>
using namespace std;
using ll = long long;
#define all(x) ::begin(x), ::end(x)
void _d(auto... x) { ((cerr << ' ' << x), ...) << endl; }
#define debug(x...) cerr << "["#x"]:", _d(x)

using ld = long double;
using pt = complex<ld>;
ld PI = acosl(-1);
constexpr ld EPS = 1e-7;

ld ang(pt a, pt b, pt c) {
    ld x = abs(b-a), y = abs(c-b), z = abs(a-c);
    return acosl((z*z - x*x - y*y) / (-2 * x * y));
}

ld cross(pt a, pt b) {
    return imag(conj(a) * b);
}

ld cross(pt a, pt b, pt c) {
    return cross(b-a, c-a);
}

ld dot(pt a, pt b) {
    return real(conj(a) * b);
}

ld dot(pt a, pt b, pt c) {
    return dot(b-a, c-b);
}

pt rotate(pt a, ld theta) {
    return a * polar(1.0L, theta);
}

pt lineIntersection(pt a, pt b, pt c, pt d) {
    ld x = cross(b - a, d - c);
    ld y = cross(c - a, d - c);
    return a + y/x*(b - a);
}

vector<pt> circleRayIntersection(pt center, ld r,
	                             pt orig, pt dir) {
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
	}}
	return result;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    int n;
    cin >> n;
    vector<pt> a(n);
    for (auto& e : a) {
        ll x, y;
        cin >> x >> y;
        e = {(ld)x, (ld)y};
    }

    ld ans = 0;
    for (int i=0; i<4; i++) a.push_back(a[i]);
    for (int i=2; i<n+2; i++) {
        pt center = (a[i-1] + a[i+1]) / 2.0L; // center of thales circle
        ld rad = abs(center - a[i-1]); // radius of thales circle

        auto valid = [&](pt p) {
            auto get = [&](int j) {
                if (i == j) return p;
                else return a[j];
            };

            for (int j=i-2; j+2<=i+2; j++) {
                if (cross(get(j), get(j+1), get(j+2)) < -EPS) return false; // check convexity
                if (dot(get(j), get(j+1), get(j+2)) < -EPS) return false; // check angle >= 90
            }
            return true;
        };

        ld orig_len = abs(a[i] - a[i-1]) + abs(a[i] - a[i+1]); // original lengths of the two edges
        auto attempt = [&](pt p) {
            if (valid(p)) {
                ans = max(ans, abs(p - a[i-1]) + abs(p - a[i+1]) - orig_len);
            }
        };

        attempt(center + rotate(a[i-1] - center, PI/2)); // middle top of thales circle

        vector<pair<pt, pt>> lines;
        lines.emplace_back(a[i-2], a[i-1]);
        lines.emplace_back(a[i-1], a[i-1] + rotate(a[i-1] - a[i-2], PI/2));

        lines.emplace_back(a[i+2], a[i+1]);
        lines.emplace_back(a[i+1], a[i+1] + rotate(a[i+1] - a[i+2], -PI/2));

        int ind = -1;
        for (auto [x, y] : lines) {
            for (auto [x2, y2] : lines) {
                
                if (abs(cross(y-x, y2-x2)) > EPS) {
                    attempt(lineIntersection(x, y, x2, y2));
                }
            }


            ind++;
            if (ind == 2) continue;
            for (pt p2 : circleRayIntersection(center, rad, x, y-x)) {
                attempt(p2);
            }
        }
    }

    cout << setprecision(12) << fixed << ans << '\n';
}
