#include <bits/stdc++.h>
using namespace std;
using i64 = long long;

int main() {
    int n; cin >> n;
    vector<int> a(n);
    for (int &x: a) cin >> x;
    sort(begin(a), end(a), greater<int>());

    int s = accumulate(begin(a), end(a), 0);
    int m = (s+1) / 2;

    i64 res = 0;
    vector<i64> dp(s+1);
    dp[0] = 1;
    for (int x: a) {
        for (int y = s; y >= x; y--) {
            if (y >= m && y-x < m) res += dp[y-x];
            dp[y] += dp[y-x];
        }
    }
    cout << res << '\n';
}
