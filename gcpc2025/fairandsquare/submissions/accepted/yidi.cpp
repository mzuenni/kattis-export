#include <bits/stdc++.h>
using namespace std;
using ll = long long;
#define all(x) ::begin(x), ::end(x)
void _d(auto... x) { ((cerr << ' ' << x), ...) << endl; }
#define debug(x...) cerr << "["#x"]:", _d(x)

int main() {
    cin.tie(0)->sync_with_stdio(0);

    int n, m;
    cin >> n >> m;
    int cnt = 0;
    vector<string> a(n);
    for (string& s : a) cin >> s, cnt += count(all(s), '#');

    int ans = 1;
    for (int x=2; x<=n; x++) {
        if (cnt % (x*x) != 0) continue;

        int cnt2 = cnt / (x*x);
        vector<vector<char>> vis(n, vector<char>(m));
        for (int i=0; i+x<=n; i++) {
            for (int j=0; j+x<=m; j++) if (!vis[i][j] && a[i][j] == '#') {
                cnt2--;
                for (int k=0; k<x; k++) {
                    for (int l=0; l<x; l++) {
                        if (a[i+k][j+l] != '#' || vis[i+k][j+l]) cnt2 = -1;
                        vis[i+k][j+l] = true;
                    }
                }
            }
        }
        if (!cnt2) ans = x;
    }
    cout << ans << '\n';
}
