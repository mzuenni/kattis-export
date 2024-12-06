#include <bits/stdc++.h>
using namespace std;
using i64 = long long;
using i128 = __int128;

int main() {
    int n; cin >> n;
    vector<pair<i64,i64>> a(n);
    for (auto &[x, y]: a) cin >> x >> y;

    i128 res = 0;
    for (int i = 0; i < n; i++) {
        for (int j = i+1; j < n; j++) {
            for (int k = j+1; k < n; k++) {
                auto [xi, yi] = a[i];
                auto [xj, yj] = a[j];
                auto [xk, yk] = a[k];
                res += (xj-xi) * (yk-yi) - (xk-xi) * (yj-yi);
            }
        }
    }

    i64 area = 0;
    for (int i = 0; i < n; i++) {
        auto [xi, yi] = a[i];
        auto [xj, yj] = a[(i+1)%n];
        area += xi*yj - xj*yi;
    }

    cout << fixed << setprecision(20) << double(res)/area << '\n';
}
