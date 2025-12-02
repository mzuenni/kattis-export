#include <bits/stdc++.h>
using namespace std;

int main() {
    vector<int> coins = {1, 2, 5, 10, 20, 50, 100, 200, 500};
    vector<int> supply = {1, 2, 1, 1, 2, 1, 1, 49, 18};

    int n; cin >> n;

    vector<int> take(9);
    auto rec = [&](const auto &self, int i) -> void {
        if (i < 9) {
            for (take[i] = 0; take[i] <= supply[i]; take[i]++) {
                self(self, i+1);
            }
        } else {
            int sum = 0;
            for (int i = 0; i < 9; i++) sum += take[i] * coins[i];
            if (sum != n) return;
            for (int i = 0; i < 9; i++) {
                bitset<5001> dp;
                dp[0] = 1;
                for (int i = 0; i < 9; i++) {
                    int k = 31 - __builtin_clz(take[i] + 1);
                    for (int j = 0; j < k; j++) {
                        dp |= dp << (coins[i] << j);
                    }
                    dp |= dp << (coins[i] * (take[i] + 1 - (1 << k)));
                }
                if (n%2 == 1 || !dp[n/2]) {
                    vector<int> b;
                    for (int i = 0; i < 9; i++) {
                        while (take[i]--) b.push_back(coins[i]);
                    }
                    cout << b.size() << '\n';
                    for (int x: b) cout << x << ' ';
                    cout << '\n';
                    exit(0);
                }
            }
        }
    };

    rec(rec, 0);
    cout << "splittable" << '\n';
}
