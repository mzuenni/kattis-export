#include <bits/stdc++.h>
using namespace std;
using i64 = long long;

int main() {
    int n, m, v, k;
    cin >> n >> m >> v >> k;
    vector<int> u(v), s(v+1);
    for (int &x: u) cin >> x;
    for (int i = 0; i < v; i++) {
        s[i+1] = s[i]+u[i];
    }
    vector<vector<pair<int,int>>> adj(n);
    while (m--) {
        int a, b, c;
        cin >> a >> b >> c;
        a--, b--;
        adj[a].emplace_back(b, c);
        adj[b].emplace_back(a, c);
    }

    vector<vector<int>> terminals(v);
    for (int i = 0; i < v; i++) {
        terminals[i] = {s[i], s[i+1]-1};
    }
    while (k--) {
        int a; cin >> a; a--;
        int i = upper_bound(begin(s), end(s), a) - 1 - begin(s);
        terminals[i].push_back(a);
    }

    vector<i64> dpLR(v), dpL(v), dpR(v), dpI(v, 1e18), dpLsR(v, 1e18), go(v);
    for (int i = 0; i < v; i++) {
        int ni = s[i+1] - s[i], ki = terminals[i].size();
        vector<vector<i64>> dp(1 << ki, vector<i64>(ni, 1e18));
        for (int j = 0; j < ki; j++) {
            dp[1 << j][terminals[i][j]-s[i]] = 0;
        }
        for (int mask = 1; mask < (1 << ki); mask++) {
            for (int smask = mask; smask > 0; smask = (smask-1) & mask) {
                for (int a = 0; a < ni; a++) {
                    dp[mask][a] = min(dp[mask][a], dp[smask][a] + dp[mask ^ smask][a]);
                }
            }
            vector<i64> dist(ni, 1e18);
            set<pair<i64,int>> todo;
            auto consider = [&](int a, i64 d) {
                if (dist[a] <= d) return;
                todo.erase({dist[a], a});
                dist[a] = d;
                todo.insert({dist[a], a});
            };
            for (int a = 0; a < ni; a++) {
                consider(a, dp[mask][a]);
            }
            while (!todo.empty()) {
                int a = begin(todo)->second;
                todo.erase(begin(todo));
                for (auto [b, c]: adj[s[i]+a]) {
                    if (b == s[i+1]%n) go[i] = c;
                    if (b < s[i] || b >= s[i+1]) continue;
                    consider(b-s[i], dist[a]+c);
                }
            }
            dp[mask] = dist;
        }
        int all_mask = (1 << ki) - 1;
        dpLR[i] = dp[all_mask][0];
        dpL[i] = dp[all_mask ^ 2][0];
        dpR[i] = dp[all_mask ^ 1][ni-1];
        dpI[i] = *min_element(begin(dp[all_mask ^ 3]), end(dp[all_mask ^ 3]));
        for (int mask = 0; mask < (1 << ki); mask++) {
            dpLsR[i] = min(dpLsR[i], dp[mask][0] + dp[all_mask ^ mask][ni-1]);
        }
    }

    for (int i = 0; i < v; i++) {
        dpLR.push_back(dpLR[i]);
        dpL.push_back(dpL[i]);
        dpR.push_back(dpR[i]);
        dpI.push_back(dpI[i]);
        dpLsR.push_back(dpLsR[i]);
        go.push_back(go[i]);
    }

    vector<i64> sumLR(2*v+1), sumgo(2*v+1);
    for (int i = 0; i < 2*v; i++) {
        sumLR[i+1] = sumLR[i] + dpLR[i];
        sumgo[i+1] = sumgo[i] + go[i];
    }

    i64 res = 1e18;
    for (int i = 0; i < v; i++) {
        res = min(res, dpLsR[i] - dpLR[i] + sumLR[v] + sumgo[v]);
    }

    auto is_empty = [&](int i) { return int(terminals[i%v].size()) == 2; };

    for (int i = 0; i < v; i++) {
        if (!is_empty(i)) {
            int j = i+1;
            while (is_empty(j)) j++;
            if (j == i+v) {
                res = min(res, dpI[i]);
            } else {
                i64 curLR = sumLR[v] - sumLR[j+1] + sumLR[i];
                i64 curgo = sumgo[v] - sumgo[j] + sumgo[i];
                res = min(res, curLR + curgo + dpL[i] + dpR[j]);
            }
        }
    }
    cout << res << '\n';
}
