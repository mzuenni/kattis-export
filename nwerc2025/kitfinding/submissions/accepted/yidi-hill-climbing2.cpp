#include <bits/stdc++.h>
using namespace std;
using ll = long long;
#define all(x) ::begin(x), ::end(x)
void _d(auto... x) { ((cerr << ' ' << x), ...) << endl; }
#define debug(x...) cerr << "["#x"]:", _d(x)

int main() {
    cin.tie(0)->sync_with_stdio(0);

    int n, m, K, I, T;
    cin >> n >> m >> K >> I >> T;

    vector<string> ans(n, string(m, '?'));
    for (int i=0; i<n; i++) for (int j=0; j<m; j++) {
        if (K) ans[i][j] = 'K', K--;
        else if (I) ans[i][j] = 'I', I--;
        else ans[i][j] = 'T';
    }

    int dx[] = {-1, 0, 1, 1, 1, 0, -1, -1};
    int dy[] = {-1, -1, -1, 0, 1, 1, 1, 0};
    const string KIT = "KIT";

    int cnt = 0;
    vector<vector<int>> st(n, vector<int>(m));

    auto calc = [&](int i, int j) {
        cnt -= st[i][j];
        st[i][j] = 0;
        if (ans[i][j] != 'K') return;
        for (int dir=0; dir<8; dir++) {
            bool good = true;
            for (int d : {1, 2}) {
                int x = i + d*dx[dir], y = j + d*dy[dir];
                if (x < 0 || x >= n || y < 0 || y >= m || ans[x][y] != KIT[d]) {
                    good = false;
                }
            }
            if (good) st[i][j]++;
        }
        cnt += st[i][j];
    };

    for (int i=0; i<n; i++) for (int j=0; j<m; j++) calc(i, j);

    auto recalc = [&](int x, int y) {
        for (int i=x-2; i<=x+2; i++) if (i >= 0 && i < n) {
            for (int j=y-2; j<=y+2; j++) if (j >= 0 && j < m) {
                calc(i, j);
            }
        }
    };

    mt19937 rng(42);
    while (cnt != 1) {
        int cnt2 = cnt;
        int x1 = rng() % n, y1 = rng() % m;
        int x2 = rng() % n, y2 = rng() % m;
        if (ans[x1][y1] == ans[x2][y2]) continue;

        swap(ans[x1][y1], ans[x2][y2]);
        recalc(x1, y1), recalc(x2, y2);

        if (abs(cnt - 1) > abs(cnt2 - 1)) {
            swap(ans[x1][y1], ans[x2][y2]);
            recalc(x1, y1), recalc(x2, y2);
        }
    }

    for (string& s : ans) cout << s << '\n';
}
