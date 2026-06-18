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

int main() {
    cin.tie(0)->sync_with_stdio(0);

    int T;
    cin >> T;
    while (T--) {
        ld d1, d2;
        cout << "? 0 1" << endl;
        cin >> d1;
        if (d1 < 0.7) {
            cout << "! 1" << endl;
            continue;
        }

        cout << "? 1 1" << endl;
        cin >> d2;

        pt p1(0, d1), p2(sqrtl(0.5)*d2, sqrtl(0.5)*d2);
        ld d = distToLine(p1, p2, {0, 0});
        cout << "! " << round(d*d*4) << endl;
    }
}
