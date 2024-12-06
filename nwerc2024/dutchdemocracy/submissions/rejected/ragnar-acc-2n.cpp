// @EXPECTED_RESULTS@: TIME_LIMIT_EXCEEDED, RUN_TIME_ERROR
#include <bits/stdc++.h>
using namespace std;

int main() {
    int n;
    cin >> n;
    vector<int> a(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }
    sort(a.rbegin(), a.rend());

    int t = accumulate(a.begin(), a.end(), 0) / 2 + 1;
    int L = n / 2;
    int R = n - L;

    long long ans = 0;
    vector<int> lsums(1, 0);
    for (int i = 0; i < L; i++) {
        vector<int> newsums;
        for (int s : lsums) {
            if (s < t && s + a[i] >= t) {
                ans++;
            }
            newsums.emplace_back(s + a[i]);
        }
        lsums.insert(lsums.end(), newsums.begin(), newsums.end());
    }
    sort(lsums.begin(), lsums.end());

    int u = accumulate(a.begin(), a.end(), 0);
    vector<int> sums(u + 2, 0);
    for (int ls : lsums) {
        sums[ls + 1]++;
    }
    for (int i = 0; i < u; i++) {
        sums[i + 1] += sums[i];
    }

    vector<int> rsums(1, 0);
    for (int i = 0; i < R; i++) {
        vector<int> newsums;
        for (int sr : rsums) {
            int h = sums[max(t - sr, 0)];
            int l = sums[max(t - sr - a[L + i], 0)];
            ans += h - l;
            newsums.push_back(sr + a[L + i]);
        }
        rsums.insert(rsums.end(), newsums.begin(), newsums.end());
    }

    cout << ans << '\n';
    return 0;
}
