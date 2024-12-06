#include <bits/stdc++.h>
using namespace std;
using i64 = long long;

string step(string s) {
    int n = size(s);
    string t(n, ' ');
    for (int i = 0; i < n; i++) {
        t[i] = s[2*i % n];
    }
    return t;
}

int main() {
    int n; cin >> n;
    i64 k; cin >> k;

    unordered_map<string,int> dp;
    string s; cin >> s;
    dp[s] = 0;

    for (int i = 1; i <= k; i++) {
        s = step(s);
        if (dp.count(s)) {
            int cyc = i - dp[s];
            for (auto [t, j]: dp) {
                if ((k-j) % cyc == 0) {
                    cout << t << '\n';
                    return 0;
                }
            }
        }
        dp[s] = i;
    }
    cout << s << '\n';
}

