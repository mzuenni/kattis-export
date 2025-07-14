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
    vector<string> a(n);
    int cnt2 = 0;
    for (auto& e : a) cin >> e, cnt2 += count(all(e), '#');

    int ans = n;
    for (int i=0; i<n; i++) {
        int cnt = 0;
        for (int j=0; j<m; j++) {
            if (a[i][j] == '#') cnt++;
            else if (cnt) {
                ans = min(ans, cnt);
                cnt = 0;
            }
        }
        if (cnt) ans = min(ans, cnt);
    }

    for (int j=0; j<m; j++) {
        int cnt = 0;
        for (int i=0; i<n; i++) {
            if (a[i][j] == '#') cnt++;
            else if (cnt) {
                ans = min(ans, cnt);
                cnt = 0;
            }
        }
        if (cnt) ans = min(ans, cnt);
    }
    while (cnt2 % (ans*ans) != 0) ans--;

    cout << ans << '\n';
}
