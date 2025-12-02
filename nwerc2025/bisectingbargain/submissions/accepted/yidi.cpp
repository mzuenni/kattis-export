#include <bits/stdc++.h>
using namespace std;
using ll = long long;
#define all(x) ::begin(x), ::end(x)
void _d(auto... x) { ((cerr << ' ' << x), ...) << endl; }
#define debug(x...) cerr << "["#x"]:", _d(x)

using bs = bitset<10'005>;
int main() {
    cin.tie(0)->sync_with_stdio(0);

    int n;
    cin >> n;

    using ar = array<int, 9>;
    ar coins = {   1,   2,   5,  10,  20,  50, 100, 200, 500};
    ar MX =    {   1,   4,   1,   1,   4,   1,   1, 500, 200}; 

    auto check = [&](ar a) {
        bs dp;
        dp[0] = 1;
        for (int i=0; i<9; i++) {
            for (int j=0; j<a[i]; j++) {
                dp |= dp << coins[i];
            }
        }
        if (n % 2 == 1 || !dp[n/2]) {
            // cout << "unsplittable\n";
            cout << accumulate(all(a), 0) << '\n';
            for (int i=0; i<9; i++) {
                for (int j=0; j<a[i]; j++) cout << coins[i] << ' ';
            }
            cout << '\n';
            exit(0);
        }
    };

    auto rec = [&](auto& self, ar a, int i, int sm) -> void {
        if (i == 9) {
            if (sm == n) check(a);
            return;
        }
        for (int j=0; j<=MX[i] && sm + coins[i] * j <= n; j++) {
            a[i] = j;
            self(self, a, i+1, sm + coins[i] * j);
        }
    };
    rec(rec, {}, 0, 0);
    cout << "splittable\n";
}
