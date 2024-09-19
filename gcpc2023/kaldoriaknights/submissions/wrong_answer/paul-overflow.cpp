#include <bits/stdc++.h>
using namespace std;
using i64 = long long;

const int N = 1e6 + 10, MOD = 1e9 + 7;
int fac[N];

int main() {
    fac[0] = 1;
    for (int n = 1; n < N; n++) {
        fac[n] = n*fac[n-1] % MOD;
    }

    int n, k;
    cin >> n >> k;
    vector<int> a(k);
    for (int &x: a) cin >> x;
    a.push_back(n - accumulate(begin(a), end(a), 0));

    vector<int> dp(k+1);
    for (int i = 0; i <= k; i++) {
        int sum = a[i];
        for (int j = i-1; j >= 0; j--) {
            dp[i] = (dp[i] - fac[sum] * dp[j]) % MOD;
            sum += a[j];
        }
        dp[i] = (dp[i] + fac[sum]) % MOD;
    }
    cout << dp[k] << '\n';
}
