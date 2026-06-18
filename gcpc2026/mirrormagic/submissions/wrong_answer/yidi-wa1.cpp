#include <bits/stdc++.h>
using namespace std;
using ll = int64_t;
#define all(x) ::begin(x), ::end(x)
#define debug(x...) [](auto&& ...y){ cerr << "["#x"]:"; ((cerr << ' ' << y), ...) << endl; }(x)

using ld = long double;
using pt = complex<ld>;

auto dot(pt a, pt b) { return real(conj(a) * b); }
auto cross(pt a, pt b) { return imag(conj(a) * b); }
auto cross(pt a, pt b, pt c) { return cross(b-a, c-a); }

pt projectToLine(pt a, pt b, pt p) {
    return a + (b - a) * dot(p - a, b - a) / norm(b - a);
}

auto distToLine(pt a, pt b, pt p) {
    return abs(cross(p - a, b - a)) / abs(b - a);
}

pt read() {
    ld x, y;
    cin >> x >> y;
    return {x, y};
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    int n;
    cin >> n;
    vector<pt> a1(n), a2(n);
    for (auto& e : a1) e = read();
    for (auto& e : a2) e = read();

    pt mid1 = accumulate(all(a1), pt{0, 0}) / (ld)n;
    pt mid2 = accumulate(all(a2), pt{0, 0}) / (ld)n;
    pt mid = (mid1 + mid2) / (ld)2;
    pt dir = mid - mid1;
    dir = dir / abs(dir) * (ld)2;
    dir = {dir.imag(), -dir.real()};
    dir += mid;

    constexpr ld EPS = 1e-7;
    for (auto& e : a1) {
        if (distToLine(mid, dir, e) < EPS || cross(mid, dir, e) > 0) {
            cout << "impossible\n";
            return 0;
        }
        e = (ld)2 * projectToLine(mid, dir, e) - e;
    }
    for (auto e : a2) {
        if (distToLine(mid, dir, e) < EPS || cross(mid, dir, e) < 0) {
            cout << "impossible\n";
            return 0;
        }
    }

    sort(all(a1), [&](auto& x, auto& y) { return pair{x.real(), x.imag()} < pair{y.real(), y.imag()}; });
    sort(all(a2), [&](auto& x, auto& y) { return pair{x.real(), x.imag()} < pair{y.real(), y.imag()}; });

    for (int i=0; i<n; i++) if (abs(a1[i] - a2[i]) > EPS) {
        cout << "impossible\n";
        return 0;
    }
    cout << "possible\n";
}
