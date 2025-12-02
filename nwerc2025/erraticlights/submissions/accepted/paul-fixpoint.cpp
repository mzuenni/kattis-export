#include <bits/stdc++.h>
using namespace std;

double dp[111][111][111];

double get(int a, int b, int c) {
    if (a >= b && b >= c) return dp[a][b][c];
    if (a >= c && c >= b) return dp[a][c][b];
    if (b >= a && a >= c) return dp[b][a][c];
    if (b >= c && c >= a) return dp[b][c][a];
    if (c >= a && a >= b) return dp[c][a][b];
    if (c >= b && b >= a) return dp[c][b][a];
    assert(0);
}

int main() {
    int n; cin >> n;

    memset(dp, 0x42, sizeof dp);
    dp[n][0][0] = 0;
    for (int z = 0; z < 1000; z++) {
        for (int a = 0; a < n; a++) {
            for (int b = 0; b <= min(a, n-a); b++) {
                int c = n-a-b;
                if (c > b) continue;
                double va = get(a, b, c) + get(a-1, b+1, c) + get(a-1, b, c+1);
                double vb = get(a+1, b-1, c) + get(a, b, c) + get(a, b-1, c+1);
                double vc = get(a+1, b, c-1) + get(a, b+1, c-1) + get(a, b, c);
                dp[a][b][c] = min(dp[a][b][c], 1 + min(va, min(vb, vc)) / 3);
            }
        }
    }

    int a = 0, b = 0, c = 0;
    string s; cin >> s;
    for (char x: s) a += x == 'r';
    for (char x: s) b += x == 'g';
    for (char x: s) c += x == 'b';
    cout << fixed << setprecision(20) << get(a, b, c) << '\n';
}
