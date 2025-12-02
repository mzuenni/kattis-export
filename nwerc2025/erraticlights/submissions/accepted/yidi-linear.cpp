#include <bits/stdc++.h>
using namespace std;
using ll = int64_t;
#define all(x) ::begin(x), ::end(x)
void _d(auto... x) { ((cerr << ' ' << x), ...) << endl; }
#define debug(x...) cerr << "["#x"]:", _d(x)

using ld = long double;

int main() {
    cin.tie(0)->sync_with_stdio(0);

    int n;
    string s;
    cin >> n >> s;
    array<int, 3> cnt = {};
    string colours = "rgb";
    for (char c : s) {
        cnt[colours.find(c)]++;
    }
    sort(all(cnt));

    vector<ld> fact(n+1, 1);
    for (int i=1; i<=n; i++) fact[i] = fact[i-1] * i;
    auto C = [&](int n2, int k2) {
        return fact[n2] / fact[k2] / fact[n2-k2];
    };

    vector<ld> p(n+1), dp(n+1);
    for (int i=0; i<=cnt[0]; i++) {
        int j = cnt[1] + i;
        p[j] = C(cnt[0], i) / powl(2, cnt[0]); 
        dp[j] = p[j] * 1.5L * cnt[0];
    }

    for (int i=n/2; i>=1; i--) {
        if (i*2 != n) p[i] += p[n-i], dp[i] += dp[n-i];

        p[i-1] += p[i];
        dp[i-1] += dp[i] + p[i] * 3;
    }

    cout << setprecision(10) << dp[0] << '\n';
}
