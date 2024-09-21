#include<bits/stdc++.h>
using namespace std;
typedef long long ll;

int main() {
    ll n, b, s, bs = 0, ss = 0, ct, rt = -1, rp;
    double p;
    cin >> n;
    tuple<ll, ll, ll> o[n];
    for (ll i = 0; i < n; ++i) {
        cin >> p >> b >> s;
        o[i] = {round(p * 100), b, s};
        bs += b;
    }
    sort(o, o + n);
    for (ll i = 0; i < n; ++i) {
        auto [cp, cb, cs] =  o[i];
        ss += cs;
        ct = cp * min(ss, bs);
        if (ct > rt) {
            rt = ct;
            rp = cp;
        }
        bs -= cb;
    }
    if (rt > 0) cout << fixed << setprecision(2) << rp / 100.0 << " " << rt / 100.0 << endl;
    else cout << "impossible" << endl;
    return 0;
}

