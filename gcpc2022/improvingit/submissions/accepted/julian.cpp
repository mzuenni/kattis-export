#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

constexpr ll INF = numeric_limits<ll>::max() / 10;

int main()
{
    int n, m;
    cin >> n >> m;
    vector<vector<ll>> cost(n);
    for (int i = 0; i < n; ++i) {
        cost[i].resize(min(m, n - i) + 1);
        for (auto& c: cost[i]) cin >> c;
    }
    cost.push_back({0});

    vector<ll> dp(n + 1, INF);
    dp[0] = cost[0][0];
    for (int i = 1; i <= n; ++i) {
        for (int j = max(0, i - m); j < i; ++j) {
            dp[i] = min(dp[i], dp[j] - cost[j][i - j] + cost[i][0]);
        }
    }

    cout << dp.back() << "\n";
}
