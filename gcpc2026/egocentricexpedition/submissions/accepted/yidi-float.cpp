#include <bits/stdc++.h>
using namespace std;
using ll = int64_t;
#define all(x) ::begin(x), ::end(x)
#define debug(x...) [](auto&& ...y){ cerr << "["#x"]:"; ((cerr << ' ' << y), ...) << endl; }(x)

using ld = float;
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
        cout << "? 0 1\n? 1 1" << endl;
        ld d1, d2;
        cin >> d1 >> d2;

        pt p1(0, d1), p2(sqrtl(0.5)*d2, sqrtl(0.5)*d2);
        ld d = distToLine(p1, p2, {0, 0});
        cout << "! " << round(d*d*4) << endl;
    }
}
