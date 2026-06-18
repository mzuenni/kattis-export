#include <bits/stdc++.h>
using namespace std;
using ll = int64_t;
#define all(x) ::begin(x), ::end(x)
#define debug(x...) [](auto&& ...y){ cerr << "["#x"]:"; ((cerr << ' ' << y), ...) << endl; }(x)

using ld = long double;
using pt = complex<ld>;

ld cross(pt a, pt b) {
    return imag(conj(a) * b);
}

ld distToLine(pt a, pt b, pt p) {
	return abs(cross(p - a, b - a)) / abs(b - a);
}

mt19937 rng(42);
int main() {
    cin.tie(0)->sync_with_stdio(0);

    vector<pt> dir;
    for (int i=0; i<=50; i++) {
        for (int j=0; j<=50; j++) {
            if (gcd(i, j) == 1) {
                dir.emplace_back(i, j);
            }
        }
    }
    sort(all(dir), [&](auto& x, auto& y){ return arg(x) < arg(y); });
    int k = ssize(dir);
    dir.push_back(dir[0]);

    int T;
    cin >> T;
    while (T--) {
        int i = rng() % k;
        pt v1 = dir[i], v2 = dir[i+1];
        while (abs(arg(v1) - arg(v2)) > 4e-4) {
            i = rng() % k;
            v1 = dir[i], v2 = dir[i+1];
        }
        cout << "? " << (int)v1.real() << ' ' << (int)v1.imag() << endl;
        cout << "? " << (int)v2.real() << ' ' << (int)v2.imag() << endl;
        ld d1, d2;
        cin >> d1 >> d2;

        pt p1 = d1 * v1/abs(v1), p2 = d2 * v2/abs(v2);
        ld d = distToLine(p1, p2, {0, 0});
        cout << "! " << round(d*d*4) << endl;
    }
}
