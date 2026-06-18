#include <bits/stdc++.h>
using namespace std;
using ll = int64_t;
#define all(x) ::begin(x), ::end(x)
#define debug(x...) [](auto&& ...y){ cerr << "["#x"]:"; ((cerr << ' ' << y), ...) << endl; }(x)

int main() {
    cin.tie(0)->sync_with_stdio(0);

    int n, k;
    cin >> n >> k;
    vector<int> p(n);
    for (int i=1; i<n; i++) cin >> p[i], p[i]--;

    vector<int> dp(n, 1);
    vector<int> ans;
    for (int i=n-1; i>=0; i--) {
        if (dp[i] >= k) dp[i] = 0, ans.push_back(i);
        dp[p[i]] = max(dp[p[i]], dp[i]+1);
    }

    cout << ssize(ans) << '\n';
    for (int e : ans) cout << e+1 << ' ';
    cout << '\n';
}
