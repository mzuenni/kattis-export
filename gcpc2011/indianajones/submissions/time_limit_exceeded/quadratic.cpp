#include <bits/stdc++.h>
using namespace std;
using ll = long long;
#define sz(x) (int)::size(x)
#define all(x) ::begin(x), ::end(x)
#define debug(x) cerr << "[" << __LINE__ << "] "#x" = " << (x) << endl

int main() {
    cin.tie(0)->sync_with_stdio(0);

    int T;
    cin >> T;
    while (T--) {
        int n, h;
        cin >> n >> h;
        vector<vector<int>> g(n);
        vector<int> deg(n);
        for (int i=0; i<h; i++) {
            int x, y;
            cin >> x >> y;
            x--, y--;
            g[x].push_back(y);
            deg[y]++;
        }

        bool recheck = false, missing = false;
        vector<bool> vis(n);
        vector<int> ans(n);
        for (int i=0; i<n; i++) {
            int cnt = 0, nxt = -1;
            for (int j=0; j<n; j++) if (!vis[j] && deg[j] == 0) {
                cnt++;
                nxt = j;
            }
            if (nxt == -1) { recheck = true; break; }
            if (cnt > 1) missing = true;
            for (int e : g[nxt]) deg[e]--;
            ans[i] = nxt + 1;
            vis[nxt] = true;
        }

        if (recheck) cout << "recheck hints";
        else if (missing) cout << "missing hints";
        else for (int e : ans) cout << e << ' ';
        cout << '\n';
    }
}
