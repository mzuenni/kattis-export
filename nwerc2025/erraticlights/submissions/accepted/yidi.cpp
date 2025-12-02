#include <bits/stdc++.h>
using namespace std;
using ll = int64_t;
#define all(x) ::begin(x), ::end(x)
void _d(auto... x) { ((cerr << ' ' << x), ...) << endl; }
#define debug(x...) cerr << "["#x"]:", _d(x)

using ld = long double;
constexpr int N = 105;
ld dp[N][3*N][3*N], p[N][3*N][3*N];

int main() {
    cin.tie(0)->sync_with_stdio(0);

    int n;
    string s;
    cin >> n >> s;
    array<int, 3> cnt = {};
    string colours = "rgb";
    for (char c : s) {
        cnt[colours.find(c)]++;
    }
    sort(all(cnt));

    n = cnt[0] + cnt[1] + cnt[2];
    p[cnt[0]][cnt[1]][cnt[2]] = 1;
    for (int i=cnt[0]; i>=1; i--) {
        for (int j=cnt[1]; j<=cnt[1]+(cnt[0]-i); j++) {
            int k = n - i - j;

            p[i-1][j+1][k] += p[i][j][k] / 2;
            p[i-1][j][k+1] += p[i][j][k] / 2;
            dp[i-1][j+1][k] += dp[i][j][k] / 2 + p[i][j][k] / 2 * 1.5L;
            dp[i-1][j][k+1] += dp[i][j][k] / 2 + p[i][j][k] / 2 * 1.5L;
        }
    }

    for (int i=n/2; i>=1; i--) {
        int j = n - i;
        if (i != j) p[0][i][j] += p[0][j][i], dp[0][i][j] += dp[0][j][i];

        p[0][i-1][j+1] += p[0][i][j];
        dp[0][i-1][j+1] += dp[0][i][j] + p[0][i][j] * 3;
    }

    cout << setprecision(10) << dp[0][0][n] << '\n';
}
