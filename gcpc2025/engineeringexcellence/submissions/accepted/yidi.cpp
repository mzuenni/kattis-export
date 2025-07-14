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
    return a * polar((ld)1.0, theta);
}

ld distToLine(pt a, pt b, pt p) {
    return abs(cross(p - a, b - a)) / abs(b - a);
}

pt lineIntersection(pt a, pt b, pt c, pt d) {
    ld x = cross(b - a, d - c);
    ld y = cross(c - a, d - c);
    return a + y/x*(b - a);
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
        pt center = (a[i-1] + a[i+1]) / (ld)2.0; // center of thales circle
        ld rad = abs(center - a[i-1]); // radius of thales circle

        ld orig_len = abs(a[i] - a[i-1]) + abs(a[i] - a[i+1]); // original lengths of the two edges
        auto attempt = [&](pt p) {
            auto get = [&](int j) {
                if (i == j) return p;
                else return a[j];
            };

            for (int j=i-2; j+2<=i+2; j++) {
                if (distToLine(get(j), get(j+1), get(j+2)) > EPS 
                        && cross(get(j), get(j+1), get(j+2)) < -EPS) return; // check convexity

                pt mid = (get(j) + get(j+2)) / (ld)2.0;
                if (abs(get(j+1) - mid) > abs(get(j) - mid) + EPS) return; // check angle >= 90
            }
            ans = max(ans, abs(p - a[i-1]) + abs(p - a[i+1]) - orig_len);
        };

        attempt(center + rotate(a[i-1] - center, PI/2)); // middle top of thales circle

        pt dir = a[i-1] - a[i-2];
        if (dot(a[i-2], a[i-1], a[i+1]) < 0) {
            dir = rotate(dir, PI/2);
        }
        {
            pt rot_dir = rotate(dir, -arg(center - a[i-1]));
            ld x = abs(rot_dir.real()), y = abs(rot_dir.imag());
            pt p = a[i-1] + dir * (4*x*rad / (2 * (x*x + y*y))); // intersection semi-circle and line
            assert(abs(abs(p - center) - rad) <= EPS);
            attempt(p);
        }

        pt dir2 = a[i+1] - a[i+2];
        if (dot(a[i-1], a[i+1], a[i+2]) < 0) {
            dir2 = rotate(dir2, -PI/2);
        }
        {
            pt rot_dir = rotate(dir2, -arg(center - a[i-1]));
            ld x = abs(rot_dir.real()), y = abs(rot_dir.imag());
            pt p = a[i+1] + dir2 * (4*x*rad / (2 * (x*x + y*y))); // intersection semi-circle and line
            assert(abs(abs(p - center) - rad) <= EPS);
            attempt(p);
        }

        if (abs(cross(dir, dir2)) > EPS) {
            pt p = lineIntersection(a[i-1], a[i-1] + dir, a[i+1], a[i+1] + dir2); // intersection line and line
            attempt(p);
        }
    }

    cout << setprecision(12) << fixed << ans << '\n';
}
