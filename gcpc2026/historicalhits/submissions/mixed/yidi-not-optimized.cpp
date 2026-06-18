// @EXPECTED_RESULTS@: ACCEPTED, TIME_LIMIT_EXCEEDED
// should probably pass, but doesn't because of constant factor
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
    auto pref = dp, suf = dp, cnt = dp;

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
        for (int l=0; l+len<=N; l++) {
            int r = l + len;
            dp[l][r] += cnt[l][r] + pref[l][r-1] + suf[l+1][r];
            pref[l][r] += pref[l][r-1];
            suf[l][r] += suf[l+1][r];

            dp[l][r] = dp[l][r] * inv[cnt[l][r]] % MOD;
            suf[l][r] %= MOD;
            pref[l][r] %= MOD;
        }

        for (auto [x, y] : a) {
            int l = min(x, y), r = min(x, y) + len;
            if (r <= max(x, y) || r > N) continue;
            ll val = dp[x+1][r] * inv[cnt[l][r]] % MOD;
            dp[l][r] = (dp[l][r] + val) % MOD;
            suf[l][r] = (suf[l][r] + dp[x+1][r]) % MOD;
        }

        for (auto [x, y] : a) {
            int l = max(x, y) + 1 - len, r = max(x, y) + 1;
            if (l > min(x, y) || l < 0) continue;
            ll val = dp[l][x] * inv[cnt[l][r]] % MOD;
            dp[l][r] = (dp[l][r] + val) % MOD;
            pref[l][r] = (pref[l][r] + dp[l][x]) % MOD;
        }
    }
    cout << dp[0][N] << '\n';
}
