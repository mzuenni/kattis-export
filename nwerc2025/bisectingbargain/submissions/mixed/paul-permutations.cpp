// @EXPECTED_RESULTS@: ACCEPTED, TIME_LIMIT_EXCEEDED
#include <bits/stdc++.h>
using namespace std;

int main() {
    vector<int> coins = {1, 2, 5, 10, 20, 50, 100, 200, 500};

    int n; cin >> n;
    do {
        int r = n;
        vector<pair<int,int>> a;
        bitset<5001> dp;
        dp[0] = 1;
        for (int x: coins) if (r >= x) {
            a.emplace_back(r/x, x);
            int k = 31 - __builtin_clz(r/x + 1);
            for (int i = 0; i < k; i++) {
                dp |= dp << (x << i);
            }
            dp |= dp << (x * (r/x + 1 - (1 << k)));
            r %= x;
        }
        if (n%2 == 1 || !dp[n/2]) {
            vector<int> b;
            for (auto [k, x]: a) while (k--) b.push_back(x);
            cout << b.size() << '\n';
            for (int x: b) cout << x << ' ';
            cout << '\n';
            return 0;
        }
    } while (next_permutation(begin(coins), end(coins)));
    cout << "splittable" << '\n';
}
