#pragma GCC optimize("Ofast")

#include <vector>
#include <numeric>
#include <iostream>
#include <algorithm>

using namespace std;

struct dsu {
    int n;
    vector<int> p, s;

    dsu(int n): n(n), p(n), s(n, 1) {
        iota(begin(p), end(p), 0);
    }

    int find(int x) {
        if (x == p[x]) return x;
        return find(p[x]);
    }

    bool unite(int x, int y) {
        x = find(x), y = find(y);
        if (x == y) return false;
        p[y] = x, s[x] += s[y];
        return true;
    }
};

int main() {
    int n, m;
    cin >> n >> m;

    dsu D(n);
    while (m--) {
        int a, b;
        cin >> a >> b;
        a--, b--;
        D.unite(a, b);
    }
    cout << *max_element(begin(D.s), end(D.s)) << '\n';
}
