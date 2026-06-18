#include <bits/stdc++.h>
using namespace std;
using ll = int64_t;
#define all(x) ::begin(x), ::end(x)
#define debug(x...) [](auto&& ...y){ cerr << "["#x"]:"; ((cerr << ' ' << y), ...) << endl; }(x)

ll multInv(ll x, ll m) { // x^{-1} mod m
	return 1 < x ? m - multInv(m % x, x) * m / x : 1;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    int n;
    cin >> n;
    vector<array<int, 2>> a(n);
    vector<int> c;
    for (auto& [x, y] : a) cin >> x >> y, c.push_back(x), c.push_back(y);
    sort(all(c));
    c.erase(unique(all(c)), c.end());
    for (auto& [x, y] : a) {
        x = lower_bound(all(c), x) - c.begin();
        y = lower_bound(all(c), y) - c.begin();
    }
    sort(all(a));

    int N = ssize(c);
    constexpr ll MOD = 998244353;
    vector<ll> fact(N+1, 1), inv(N+1, 1);
    for (int i=2; i<=N; i++) fact[i] = fact[i-1] * i % MOD, inv[i] = multInv(i, MOD);

    vector<vector<ll>> dp(N+1, vector<ll>(N+1));
    auto cnt = dp;
    vector<ll> pref1(N+1), suf1(N+1);

    for (auto [x, y] : a) {
        cnt[min(x, y)][max(x, y)+1]++;
    }
    for (int len=1; len<=N; len++) {
        for (int l=0; l+len<=N; l++) {
            int r = l + len;
            cnt[l][r] += cnt[l][r-1] + cnt[l+1][r] - cnt[l+1][r-1];
        }
    }

    for (int len=1; len<=N; len++) {
        vector<ll> pref2(N+1), suf2(N+1);
        for (int l=0; l+len<=N; l++) {
            int r = l + len;
            dp[l][r] += cnt[l][r] + pref1[l] + suf1[l+1];
            pref2[l] += pref1[l];
            suf2[l] += suf1[l+1];

            dp[l][r] = dp[l][r] * inv[cnt[l][r]] % MOD;
        }

        for (auto [x, y] : a) {
            int l = min(x, y), r = min(x, y) + len;
            if (r > max(x, y) && r <= N) {
                ll val = dp[x+1][r] * inv[cnt[l][r]] % MOD;
                dp[l][r] = (dp[l][r] + val) % MOD;
                suf2[l] = (suf2[l] + dp[x+1][r]) % MOD;
            }

            l = max(x, y) + 1 - len, r = max(x, y) + 1;
            if (l <= min(x, y) && l >= 0) {
                ll val = dp[l][x] * inv[cnt[l][r]] % MOD;
                dp[l][r] = (dp[l][r] + val) % MOD;
                pref2[l] = (pref2[l] + dp[l][x]) % MOD;
            }
        }
        swap(suf1, suf2);
        swap(pref1, pref2);
    }
    cout << dp[0][N] << '\n';
}
