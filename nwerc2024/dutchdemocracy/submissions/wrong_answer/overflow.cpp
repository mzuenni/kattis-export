#include <bits/stdc++.h>
using namespace std;

int main() {
    int n;
    cin >> n;
    vector<int> p(n);
    for (int i = 0; i < n; i++) {
        cin >> p[i];
    }
    sort(p.rbegin(), p.rend());
    int sum = accumulate(p.begin(), p.end(), 0);
    vector<int> dp(sum + 1);
    dp[0] = 1;
    long long ans = 0;
    for (int i = 0; i < n; i++) {
        for (int j = sum; j >= p[i]; j--) {
            if (j > sum - j && (j - p[i]) <= sum - (j - p[i])) {
                ans += dp[j - p[i]];
            }
            dp[j] += dp[j - p[i]];
        }
    }
    cout << ans << '\n';
}
