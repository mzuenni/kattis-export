// @EXPECTED_RESULTS@: ACCEPTED, TIME_LIMIT_EXCEEDED
// Ideally we would like this to time out, but that's not feasible if we also
// want Python/Haskell to pass. Decision is to ignore this submission as the
// optimizations are arguably harder to come up with than the intended
// solution.
#include <bits/stdc++.h>
using namespace std;
using ll = long long;
#define all(x) ::begin(x), ::end(x)
void _d(auto... x) { ((cerr << ' ' << x), ...) << endl; }
#define debug(x...) cerr << "["#x"]:", _d(x)

constexpr int N = 5005;
int dp[N][N];

int main() {
    cin.tie(0)->sync_with_stdio(0);

    int n, m;
    cin >> n >> m;
    int cnt = 0;
    vector<string> a(n);
    for (string& s : a) cin >> s, cnt += count(all(s), '#');

    int ans = 1;
    string s = "#";
    vector<pair<int, int>> idk;
    for (int x=2; x<=n; x++) {
        s += '#';
        idk.clear();
        // if (cnt % (x*x) != 0) continue;

        int cnt2 = 0;
        for (int i=0; i<n; i++) {
            for (int j=0; j+x<=m; j++) if (a[i][j] == '#') {
                if (a[i].substr(j, x) != s) goto out;
                idk.emplace_back(i, j);
                dp[i][j] = x;
                cnt2 += x;
                j += x-1;
            }
        }
        
        for (auto [i, j] : idk) if (dp[i][j] == x) {
            for (int k=0; k<x; k++) {
                if (dp[i+k][j] != x) goto out;
                dp[i+k][j] = 0;
            }
        }

        if (cnt2 == cnt) ans = x;
        out:;
    }
    cout << ans << '\n';
}
