#include <bits/stdc++.h>
using namespace std;
using ll = int64_t;
#define all(x) ::begin(x), ::end(x)
void _d(auto... x) { ((cerr << ' ' << x), ...) << endl; }
#define debug(x...) cerr << "["#x"]:", _d(x)

using ld = long double;
constexpr int N = 105;

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

    vector<vector<ld>> C(N+1, vector<ld>(N+1));
    auto C2 = C;
    C[0][0] = 1;
    for (int i=0; i<N; i++) {
        for (int j=0; j<=i; j++) {
            C[i+1][j] += C[i][j] / 2;
            C[i+1][j+1] += C[i][j] / 2;
            C2[i+1][j] += C2[i][j] / 2 + C[i][j] * 0.75;
            C2[i+1][j+1] += C2[i][j] / 2 + C[i][j] * 0.75;
        }
    }

    vector<ld> p(n+1), dp(n+1);
    for (int i=0; i<=cnt[0]; i++) {
        int j = cnt[1] + i;
        p[j] = C[cnt[0]][i]; 
        dp[j] = C2[cnt[0]][i];
    }

    for (int i=n/2; i>=1; i--) {
        int j = n - i;
        if (i != j) p[i] += p[j], dp[i] += dp[j];

        p[i-1] += p[i];
        dp[i-1] += dp[i] + p[i] * 3;
    }

    cout << setprecision(10) << dp[0] << '\n';
}
