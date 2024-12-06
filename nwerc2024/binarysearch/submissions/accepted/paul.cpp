#include <bits/stdc++.h>
using namespace std;

int main() {
    int n, m;
    cin >> n >> m;

    vector<int> a(n);
    for (int &x: a) cin >> x;

    vector<int> indeg(4*n);
    vector<vector<int>> adj(4*n);

    auto add_edge = [&](int x, int y) {
        int i = 2*!a[y] + a[x];
        int j = 2*a[x] + a[y];
        adj[j*n + y].push_back(i*n + x);
        indeg[i*n + x]++;
    };

    while (m--) {
        int x, y;
        cin >> x >> y;
        x--, y--;
        add_edge(x, y);
        add_edge(y, x);
    }

    queue<int> todo;
    for (int x = 0; x < 4*n; x++) {
        if (!indeg[x]) todo.push(x);
    }

    vector<int> dp(4*n);
    while (!todo.empty()) {
        int x = todo.front();
        todo.pop();
        for (int y: adj[x]) {
            dp[y] = max(dp[y], dp[x]+1);
            if (!--indeg[y]) todo.push(y);
        }
    }

    if (accumulate(begin(indeg), end(indeg), 0) > 0) {
        cout << "infinity" << '\n';
    } else {
        int res = 1e9;
        for (int i = 0; i < 4; i++) {
            res = min(res, 2 + *max_element(begin(dp)+i*n, begin(dp)+(i+1)*n));
        }
        set<int> s(begin(a), end(a));
        if (ssize(s) == 1) res = 1;
        cout << res << '\n';
    }
}
