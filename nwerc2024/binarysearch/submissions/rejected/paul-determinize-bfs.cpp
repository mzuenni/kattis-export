// @EXPECTED_RESULTS@: TIME_LIMIT_EXCEEDED, RUN_TIME_ERROR, WRONG_ANSWER

// Use the classical powerset construction to construct a DFA.
#include <array>
#include <iostream>
#include <map>
#include <numeric>
#include <queue>
#include <vector>
using namespace std;
using i64 = long long;

const int N = 3e5 + 5;
const i64 MOD = i64(1e18) + 3;
i64 p2[N];

int X = 0;
int mark[N];

int main() {
    p2[0] = 1;
    for (int n = 1; n < N; n++) {
        p2[n] = 2*p2[n-1] % MOD;
    }

    int n, m;
    cin >> n >> m;
    vector<int> a(n);
    for (int &x: a) cin >> x;

    vector<vector<int>> adj(n);
    while (m--) {
        int u, v;
        cin >> u >> v;
        u--, v--;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    vector<vector<int>> states;
    vector<array<int,2>> go;
    map<i64,int> id;

    auto get = [&](const vector<int> &st) {
        i64 hash = 0;
        for (int x: st) hash = (hash + p2[x]) % MOD;

        if (id.count(hash)) return id[hash];
        id[hash] = size(go);
        states.push_back(st);
        go.push_back({-1, -1});
        return id[hash];
    };

    vector<int> init(n);
    iota(begin(init), end(init), 0);
    get(init);

    for (int cur = 0; cur < ssize(states); cur++) {
        const auto &st = states[cur];

        X++;
        vector<int> st0, st1;
        for (int x: st) for (int y: adj[x]) {
            if (mark[y] == X) continue;
            mark[y] = X;
            (a[y] ? st1 : st0).push_back(y);
        }
        go[cur][0] = get(st0);
        go[cur][1] = get(st1);
    }

    if (!id.count(0)) {
        cout << "infinity" << '\n';
        return 0;
    }

    int k = size(go);
    vector<vector<int>> rev_adj(k);
    for (int i = 0; i < k; i++) {
        for (int j: go[i]) rev_adj[j].push_back(i);
    }

    vector<int> dist(k, -1);
    queue<int> todo;
    dist[id[0]] = 0;
    todo.push(id[0]);
    while (!todo.empty()) {
        int i = todo.front();
        todo.pop();
        for (int j: rev_adj[i]) {
            if (dist[j] != -1) continue;
            dist[j] = dist[i] + 1;
            todo.push(j);
        }
    }
    cout << dist[0] << '\n';
}
