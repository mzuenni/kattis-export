#include <bits/stdc++.h>
using namespace std;
using ll = int64_t;
#define all(x) ::begin(x), ::end(x)
void _d(auto... x) { ((cerr << ' ' << x), ...) << endl; }
#define debug(x...) cerr << "["#x"]:", _d(x)

int main() {
    cin.tie(0)->sync_with_stdio(0);

    int n;
    cin >> n;
    vector<array<int, 3>> a;
    for (int i=0; i<n; i++) {
        int x;
        cin >> x;
        x--;
        if (i <= x) a.push_back({i, x-i, 1});
        if (i + x >= n - 1) a.push_back({x - (n-1-i), n-1-i, 0});
    }
    sort(all(a));

    vector<int> dp(n, 1e9);
    int ans = n;
    for (int left=0, ptr=0; left<n; left++) {
        vector<pair<int, int>> rem;
        while (ptr < ssize(a) && a[ptr][0] == left) {
            auto [l, r, type] = a[ptr++];
            int i = upper_bound(all(dp), r) - dp.begin();
            ans = min(ans, n - i - 1);

            if (type == 0) dp[i] = r+1;
            else rem.emplace_back(i, r);
        }

        for (auto [i, x] : rem) dp[i] = min(dp[i], x);
    }
    cout << ans << '\n';
}
