#include <bits/stdc++.h>
using namespace std;

int main() {
    int n, m, x, y;
    cin >> n >> m >> x >> y;
    vector<int> a(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }
    vector<int> b(m);
    for (int i = 0; i < m; i++) {
        cin >> b[i];
    }
    sort(a.rbegin(), a.rend());
    sort(b.rbegin(), b.rend());

    int low = -1, high = n + 1;
    while (high - low > 1) {
        int mid = (high + low) >> 1;
        int j = 0;
        for (int i = 0; i < n; i++) {
            if (j < m && b[j] <= a[i]) {
                if (i >= n - mid) {
                    j = min(m, j + y);
                } else {
                    j = min(m, j + x);
                }
            }
        }
        if (j == m) {
            low = mid;
        } else {
            high = mid;
        }
    }
    if (low == -1) cout << "impossible\n";
    else cout << low << '\n';
    return 0;
}
