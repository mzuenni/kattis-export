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

        ld orig_len = abs(a[i] - a[i-1]) + abs(a[i] - a[i+1]); // original lengths of the two edges
        auto attempt = [&](pt p) {
            auto get = [&](int j) {
                if (i == j) return p;
                else return a[j];
            };

            for (int j=i-2; j+2<=i+2; j++) {
                if (cross(get(j), get(j+1), get(j+2)) < -EPS) return; // check convexity
                if (dot(get(j), get(j+1), get(j+2)) < -EPS) return; // check angle >= 90
            }
            ans = max(ans, abs(p - a[i-1]) + abs(p - a[i+1]) - orig_len);
        };

        attempt(center + rotate(a[i-1] - center, PI/2)); // middle top of thales circle
                                                         //
        auto bin_search = [&](pt p, pt dir) {
            dir /= abs(dir);
            ld l = 0, r = 4e9;
            for (int it=0; it<70; it++) {
                ld m = (l+r) / 2;
                if (abs(p + m*dir - center) <= rad) l = m;
                else r = m;
            }
            attempt(p + l*dir);
        };

        pt dir = a[i-1] - a[i-2];
        if (dot(a[i-2], a[i-1], a[i+1]) < 0) {
            dir = rotate(dir, PI/2);
        }
        bin_search(a[i-1], dir);

        pt dir2 = a[i+1] - a[i+2];
        if (dot(a[i-1], a[i+1], a[i+2]) < 0) {
            dir2 = rotate(dir2, -PI/2);
        }
        bin_search(a[i+1], dir2);

        if (abs(cross(dir, dir2)) > EPS) {
            pt p = lineIntersection(a[i-1], a[i-1] + dir, a[i+1], a[i+1] + dir2); // intersection line and line
            attempt(p);
        }
    }

    cout << setprecision(12) << fixed << ans << '\n';
}
