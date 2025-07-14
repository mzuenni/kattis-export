#include <bits/stdc++.h>
using namespace std;
using ll = long long;
#define all(x) ::begin(x), ::end(x)
void _d(auto... x) { ((cerr << ' ' << x), ...) << endl; }
#define debug(x...) cerr << "["#x"]:", _d(x)

int main() {
    cin.tie(0)->sync_with_stdio(0);

    int n, m, vil, k;
    cin >> n >> m >> vil >> k;
    vector<int> a(n, -1), a2(vil+1);
    for (int i=0, j=0; i<vil; i++) {
        int x;
        cin >> x;
        a2[i+1] = a2[i] + x;
        while (x--) a[j++] = i;
    }
    vector<vector<pair<int, ll>>> g(n);
    vector<ll> connecting(vil);
    for (int i=0; i<m; i++) {
        int u, v, w;
        cin >> u >> v >> w;
        u--, v--;
        if (u > v) swap(u, v);
        if (a[u] != a[v]) {
            if (u == 0 && v == n-1) connecting.back() = w;
            else connecting[a[u]] = w;
        } else {
            g[u].emplace_back(v, w);
            g[v].emplace_back(u, w);
        }
    }
    vector<bool> term(n);
    vector<int> cnt(vil);
    for (int i=0; i<k; i++) {
        int u;
        cin >> u;
        u--;
        term[u] = true;
        cnt[a[u]]++;
    }

    auto calc = [&](int village) -> array<ll, 5> {
        int offset = a2[village];
        int N = a2[village+1] - offset;
        if (N == 1) {
            return {0, 0, 0, 0, 0};
        }
        vector<int> t = {0, N-1};
        for (int i=1; i<N-1; i++) if (term[offset + i]) t.push_back(i);
        k = t.size();

        vector<vector<ll>> dp(N, vector<ll>(1<<k, 1e18));
        for (int i=0; i<k; i++) dp[t[i]][1<<i] = 0;
        for (int i=0; i<N; i++) dp[i][0] = 0;
        
        for (int msk=1; msk<(1<<k); msk++) {
            for (int i=0; i<N; i++) {
                for (int msk2=msk; msk2>0; msk2 = (msk2-1) & msk) {
                    dp[i][msk] = min(dp[i][msk], dp[i][msk2] + dp[i][msk^msk2]);
                }
            }

            priority_queue<array<ll, 2>, vector<array<ll, 2>>, greater<>> q;
            for (int i=0; i<N; i++) q.push({dp[i][msk], i});
            while (!q.empty()) {
                auto [val, u] = q.top();
                q.pop();
                if (dp[u][msk] != val) continue;
                for (auto [v, w] : g[offset + u]) {
                    v -= offset;
                    if (dp[v][msk] > dp[u][msk] + w) {
                        dp[v][msk] = dp[u][msk] + w;
                        q.push({dp[v][msk], v});
                    }
                }
            }
        }

        int super = (1<<k) - 1;
        int super2 = super, super3 = super, super4 = super;
        if (!term[offset + 0]) super3 ^= 1, super4 ^= 1;
        if (!term[offset + N-1]) super2 ^= 2, super4 ^= 2;
        
        ll x = 0;
        for (int i=0; i<k; i++) if (super4 >> i & 1) x = dp[t[i]][super4];

        ll y = 1e18;
        for (int i=1; i<(1<<k); i += 4) {
            y = min(y, dp[0][i] + dp[N-1][super ^ i]);
        }

        dp[0][super2] = 1e18;
        return {dp[0][super], dp[0][super2], dp[N-1][super3], x, y};
    };

    vector<array<ll, 5>> dp(vil);
    for (int i=0; i<vil; i++) dp[i] = calc(i);

    vector<ll> pref(3*vil+1);
    for (int i=0; i<3*vil; i++) pref[i+1] = pref[i] + dp[i%vil][0];

    ll ans = 1e18;
    ll sm = accumulate(all(connecting), 0LL);
    for (int l=0, r=0; l<vil; l=r) {
        r = l + 1;
        ll c = sm - connecting[l];
        while (cnt[r % vil] == 0) c -= connecting[r % vil], r++;

        if (r == l + vil) {
            ans = min(ans, dp[r % vil][3]);
        } else {
            c += dp[l][1] + dp[r%vil][2];
            c += pref[l+vil] - pref[r+1];
            ans = min(ans, c);
        }
        ans = min(ans, dp[l][4] + sm + pref[l+vil] - pref[l+1]);
    }
    cout << ans << '\n';
}
