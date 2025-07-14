#include <bits/stdc++.h>
using namespace std;
using ll = long long;
#define all(x) ::begin(x), ::end(x)
void _d(auto... x) { ((cerr << ' ' << x), ...) << endl; }
#define debug(x...) cerr << "["#x"]:", _d(x)

using ld = long double;
using pt = complex<ld>;
ld PI = acosl(-1);

ld ang(pt a, pt b, pt c) {
    ld x = abs(b-a), y = abs(c-b), z = abs(a-c);
    return acosl((z*z - x*x - y*y) / (-2 * x * y));
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
        ld fact = -1;
        // only one of the three if statements should trigger
        // (except maybe floating point stuff but it should not matter then)
        ld alpha = ang(a[i-2], a[i-1], a[i+1]);
        if (alpha < PI/4) fact = sin(alpha) + sin(PI/2 - alpha);

        alpha = ang(a[i-1], a[i+1], a[i+2]);
        if (alpha < PI/4) fact = sin(alpha) + sin(PI/2 - alpha);

        if (fact < 0) fact = sqrtl(2);
        ld len = abs(a[i] - a[i-1]) + abs(a[i] - a[i+1]);
        ans = max(ans, fact*abs(a[i+1]-a[i-1]) - len);
    }

    cout << setprecision(12) << fixed << ans << '\n';
}
