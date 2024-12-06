#include <bits/stdc++.h>
using namespace std;

int main() {
    int n, m;
    cin >> n >> m;
    vector<int> a(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }
    vector<vector<int>> g(4 * n);
    vector<int> deg(4 * n);
    auto add_edge = [&](int from, int to) {
        int t = a[from] ^ a[to] ^ (2 * a[from]);
        from = from + t * n;
        to = to + ((t + 1) % 4) * n;
        g[from].emplace_back(to);
        deg[to]++;
    };
    for (int i = 0; i < m; i++) {
        int x, y;
        cin >> x >> y;
        x--;
        y--;
        add_edge(x, y);
        add_edge(y, x);
    }

    queue<int> que;
    for (int i = 0; i < 4 * n; i++) {
        if (deg[i] == 0) {
            que.emplace(i);
        }
    }
    vector<int> order;
    while (!que.empty()) {
        int v = que.front();
        que.pop();
        order.emplace_back(v);
        for (int to : g[v]) {
            deg[to]--;
            if (deg[to] == 0) {
                que.emplace(to);
            }
        }
    }
    if (int(order.size()) < 4 * n) {
        cout << "infinity" << '\n';
        return 0;
    }

    vector<int> dp(4 * n);
    reverse(order.begin(), order.end());
    for (int v : order) {
        for (int to : g[v]) {
            dp[v] = max(dp[v], dp[to] + 1);
        }
    }
    int ans = INT_MAX;
    for (int i = 0; i < 4; i++) {
        ans = min(ans, *max_element(dp.begin() + i * n, dp.begin() + (i + 1) * n));
    }
    ans += 2;
    if (a == vector<int>(n, a[0])) {
        ans = 1;
    }
    cout << ans << '\n';
    return 0;
}
