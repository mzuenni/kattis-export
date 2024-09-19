#include<bits/stdc++.h>
using namespace std;
typedef long long ll;

char r[3024][3024];

int main() {
    ll x, y, n = 0;
    cin >> y >> x;
    for (ll i = 0; i < y; ++i)
        for (ll j = 0; j < x; ++j) {
            cin >> r[i][j];
            if (r[i][j] == 'C') ++n;
        }
    ll ye[x], x0 = 0;
    for (ll i = 0; i < x; ++i) ye[i] = y;
    ll res = 0;
    while (n) {
        ++res;
        ll y0 = 0;
        for (ll i = x0; i < x; ++i) {
            ll y0x = y0;
            for (ll j = y0; j < ye[i]; ++j)
                if (r[j][i] == 'C')
                    y0 = max(y0, j), --n;
            ye[i] = y0x;
            if (ye[i] == 0) x0 = i + 1;
        }
    }
    cout << res << endl;
    return 0;
}
