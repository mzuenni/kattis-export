#include <bits/stdc++.h>
using namespace std;

int main() {
    int n; cin >> n;

    long base = 0;
    map<int,int> rsum;
    map<int,vector<int>> diffs;
    for (int i = 0; i < 2*n; i++) {
        int l, r, c;
        cin >> l >> r >> c;
        rsum[c] += r, base += r;
        diffs[c].push_back(l-r);
    }

    vector<long> dp = {base};
    for (auto [c, v]: diffs) {
        int m = dp.size(), k = v.size(), nm = min(n+1, m+k);
        sort(begin(v), end(v), greater());
        vector<long> s(k+1);
        for (int i = 0; i < k; i++) {
            s[i+1] = s[i]+v[i];
        }

        vector<long> ndp(nm);
        for (int i = 0; i < m; i++) {
            for (int j = 0; j <= k && i+j < nm; j++) {
                ndp[i+j] = max(ndp[i+j], dp[i] + s[j] + min(j, k-j) * c);
            }
        }
        dp = ndp;
    }
    cout << dp[n] << '\n';
}
