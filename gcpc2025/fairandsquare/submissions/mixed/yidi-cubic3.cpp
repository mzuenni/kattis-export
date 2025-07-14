// @EXPECTED_RESULTS@: ACCEPTED, TIME_LIMIT_EXCEEDED
#include <bits/stdc++.h>
using namespace std;
using ll = long long;
#define all(x) ::begin(x), ::end(x)
void _d(auto... x) { ((cerr << ' ' << x), ...) << endl; }
#define debug(x...) cerr << "["#x"]:", _d(x)

constexpr int N = 5000;
short dp[N][N];

int main() {
    cin.tie(0)->sync_with_stdio(0);

    int n, m;
    cin >> n >> m;
    int cnt = 0;
    vector<string> a(n);
    for (string& s : a) cin >> s, cnt += count(all(s), '#');

    int ans = 1;
    string s = "#";
    for (int x=2; x<=n; x++) {
        s += '#';
        // if (cnt % (x*x) != 0) continue;

        int cnt2 = 0;
        for (int i=0; i<n; i++) {
            for (int j=0; j<m; j++) {
                if (dp[i][j] == x) {
                    j += x-1;
                    continue;
                }
                if (a[i][j] == '#') {
                    if (i+x > n || j+x > m) goto out;
                    for (int k=0; k<x; k++) {
                        if (a[i+k].substr(j, x) != s) goto out;
                        dp[i+k][j] = x;
                        cnt2 += x;
                    }
                    j += x - 1;
                }
            }
        }
        if (cnt2 == cnt) ans = x;
        out:;
    }
    cout << ans << '\n';
}
