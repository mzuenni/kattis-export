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

    vector<int> rsums(1, 0);
    for (int i = 0; i < R; i++) {
        vector<int> newsums;
        for (int sr : rsums) {
            auto h = lower_bound(lsums.begin(), lsums.end(), t - sr);
            auto l = lower_bound(lsums.begin(), lsums.end(), t - sr - a[L + i]);
            ans += int(h - l);
            newsums.emplace_back(sr + a[L + i]);
        }
        rsums.insert(rsums.end(), newsums.begin(), newsums.end());
    }

    cout << ans << '\n';
    return 0;
}
