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

    mt19937 rng(42);

    vector<string> ans(n, string(m, '?'));
    for (int i=0; i<n; i++) for (int j=0; j<m; j++) {
        while (ans[i][j] == '?') {
            int k = rng() % 3;
            if (k == 0 && K) ans[i][j] = 'K', K--;
            else if (k == 1 && I) ans[i][j] = 'I', I--;
            else if (k == 2 && T) ans[i][j] = 'T', T--;
        }
    }

    int dx[] = {-1, 0, 1, 1, 1, 0, -1, -1};
    int dy[] = {-1, -1, -1, 0, 1, 1, 1, 0};
    const string KIT = "KIT";
    auto calc = [&]() {
        int cnt = 0;
        for (int i=0; i<n; i++) for (int j=0; j<m; j++) if (ans[i][j] == 'K') {
            for (int dir=0; dir<8; dir++) {
                bool good = true;
                for (int d : {1, 2}) {
                    int x = i + d*dx[dir], y = j + d*dy[dir];
                    if (x < 0 || x >= n || y < 0 || y >= m || ans[x][y] != KIT[d]) {
                        good = false;
                    }
                }
                if (good) cnt++;
            }
        }
        return cnt;
    };

    constexpr int IT = 3;
    while (calc() != 1) {
        int cnt = calc();
        auto ans2 = ans;
        for (int it=0; it<IT; it++) {
            int x1 = rng() % n, y1 = rng() % m;
            int x2 = rng() % n, y2 = rng() % m;
            if (ans[x1][y1] == ans[x2][y2]) {
                it--;
                continue;
            }
            swap(ans[x1][y1], ans[x2][y2]);
        }
        int cnt2 = calc();
        if (abs(cnt2 - 1) > abs(cnt - 1)) ans = ans2;
    }

    for (string& s : ans) cout << s << '\n';
}
