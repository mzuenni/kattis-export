#include <bits/stdc++.h>
using namespace std;

int main() {
    int n, m, k;
    cin >> n >> m >> k;
    vector<vector<pair<int, int>>> g(n);
    for (int i = 0; i < m; i++) {
        int x, y, w;
        cin >> x >> y >> w;
        x--;
        y--;
        g[x].emplace_back(y, w);
        g[y].emplace_back(x, w);
    }

    const long long inf = 1e18;
    auto dijkstra = [&](int r) {
        vector<long long> d(n, inf);
        d[r] = 0;
        priority_queue<pair<long long, int>, vector<pair<long long, int>>, greater<>> pq;
        pq.emplace(d[r], r);
        while (!pq.empty()) {
            auto [dv, v] = pq.top();
            pq.pop();
            if (d[v] != dv) {
                continue;
            }
            for (auto [to, w] : g[v]) {
                if (d[to] > d[v] + w) {
                    d[to] = d[v] + w;
                    pq.emplace(d[to], to);
                }
            }
        }
        return d;
    };

    auto d0 = dijkstra(0);
    auto d1 = dijkstra(n - 1);

    vector<pair<long long, long double>> e;
    bool is_reachable = false;

    for (int i = 0; i < k; i++) {
        int v;
        long double p;
        cin >> v >> p;
        v--;
        if (d0[v] == inf || d1[v] == inf) {
            continue;
        }
        e.emplace_back(d0[v] + d1[v], p);
        if (p == 1) {
            is_reachable = true;
        }
    }

    if (!is_reachable) {
        cout << "impossible" << '\n';
        return 0;
    }

    long double q = 1;
    long double ans = 0;
    sort(e.begin(), e.end());
    for (auto [d, p] : e) {
        ans += q * p * d;
        q *= 1 - p;
    }
    cout << fixed << setprecision(12) << ans << '\n';
}
