#include <bits/stdc++.h>
using namespace std;

int main() {
    int n;
    cin >> n;
    vector<int> p(n);
    for (int i = 0; i < n; i++) {
        cin >> p[i];
    }
    long long ans = 0;
    int total = accumulate(p.begin(), p.end(), 0);
    for (long long t = 1; t < (1LL << n); t++) {
        int mn = INT_MAX;
        int sum = 0;
        for (int i = 0; i < n; i++) {
            if (t & (1LL << i)) {
                mn = min(mn, p[i]);
                sum += p[i];
            }
        }
        if (sum > total - sum && (sum - mn) <= total - (sum - mn)) {
            ans++;
        }
    }
    cout << ans << endl;
}
