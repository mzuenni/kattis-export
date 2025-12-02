#include <bits/stdc++.h>
using namespace std;

void make_step(vector<int> &a, int i, int j) {
    vector<int> b(begin(a)+i, begin(a)+i+3);
    a.erase(begin(a)+i, begin(a)+i+3);
    a.insert(begin(a)+j, begin(b), end(b));
}

int main() {
    int n; cin >> n;
    vector<int> a(n);
    for (int &x: a) cin >> x, x--;

    vector<pair<int,int>> res;

    auto add_step = [&](int i, int j) {
        if (i == j) return;
        res.emplace_back(i+1, j+1);
        make_step(a, i, j);
    };

    for (int i = n-1; i >= 8; i--) {
        for (int j = 0; j < i; j++) {
            if (a[j] != i) continue;
            if (j < 2) add_step(0, i/2);
            else add_step(j-2, i-2);
        }
        assert(a[i] == i);
    }

    queue<vector<int>> todo;
    map<vector<int>,pair<int,int>> last_step;

    auto consider = [&](vector<int> p, int i, int j) {
        if (last_step.count(p)) return;
        last_step[p] = {i, j};
        todo.push(p);
    };

    int m = min(n, 8);
    vector<int> p(m);
    iota(begin(p), end(p), 0);
    consider(p, -1, -1);

    while (!todo.empty()) {
        auto p = todo.front();
        todo.pop();
        for (int i = 0; i < m-2; i++) {
            for (int j = 0; j < m-2; j++) {
                if (i == j) continue;
                vector<int> q = p;
                make_step(q, i, j);
                consider(q, i, j);
            }
        }
    }

    a.resize(m);
    while (true) {
        auto [i, j] = last_step[a];
        if (i < 0) break;
        add_step(j, i);
    }

    cout << res.size() << '\n';
    for (auto [i, j]: res) {
        cout << i << ' ' << j << '\n';
    }
}
