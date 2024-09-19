#include<bits/stdc++.h>
using namespace std;
typedef long long ll;

int main() {
    ll n = 0, a, b;
    cin >> n;
    pair<ll, ll> in[n];
    for (ll i = 0; i < n; ++i) {
        cin >> a >> b;
        in[i] = {a, b};
    }
    sort(in, in + n);
    ll d[n], j[n + 1], dp[n][4];
    iota(d, d + n, 0);
    memset(j, -1, sizeof(j));
    j[n] = n - 1;
    for (ll i = 1; i < n; ++i) {
        for (ll k = d[i - 1]; k < i; ++k)
            if (in[k].second >= in[i].first) {
                d[i] = k;
                break;
            }
        for (ll k = j[n - i + 1]; k >= 0; --k)
            if (in[k].second < in[n - i].first) {
                j[n - i] = k;
                break;
            }
    }
    memset(dp, 0x3f, sizeof(dp));
    for (ll k = 0; k < 4; ++k)
        for (ll i = 0; i < n; ++i) {
            if (j[i] < 0) dp[i][k] = 1;
            else {
                ll x = i;
                for (ll k2 = 0; k2 <= k; ++k2) {
                    x = d[x];
                    if (j[x] < 0) {
                        dp[i][k] = 1;
                        break;
                    }
                    dp[i][k] = min(dp[i][k], dp[j[x]][k - k2] + 1);
                }
            }
        }
    for (ll k = 1; k < 4; ++k)
        if (dp[n - 1][k] < dp[n - 1][0]) {
            cout << k << endl;
            return 0;
        }
    cout << "impossible" << endl;
    return 0;
}
