#include <bits/stdc++.h>
using namespace std;
using ll = long long;
#define all(x) ::begin(x), ::end(x)
#define debug(x) cerr << "[" << __LINE__ << "] "#x" = " << (x) << endl

struct Union {
    vector<int> par;

    Union(int n) : par(n, -1) {}

    int find(int i) {
        if (par[i] < 0) return i;
        return par[i] = find(par[i]);
    }

    bool join(int i, int j) {
        i = find(i), j = find(j);
        if (i == j) return false;
        par[i] += par[j];
        par[j] = i;
        return true;
    }
};

vector<int> val;
vector<vector<pair<int, int>>> g;
Union u(1);
vector<bool> rea;

ll ans = 0;
void dfs(int cur, int par) {
    for (auto [e, w] : g[cur]) if (e != par) {
        dfs(e, cur);
        if (val[e]) u.join(cur, e), ans += w, rea[e] = true, rea[cur] = true;
        val[cur] ^= val[e];
    }
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    int n;
    cin >> n;

    g.resize(n);
    for (int i=1; i<n; i++) {
        int x, y, z;
        cin >> x >> y >> z;
        x--, y--;
        g[x].emplace_back(y, z);
        g[y].emplace_back(x, z);
    }

    u = Union(n);

    int m;
    cin >> m;
    val.resize(n);
    rea.resize(n);
    while (m--) {
        int x, y;
        cin >> x >> y;
        x--, y--;
        val[x] ^= 1, val[y] ^= 1;
        u.join(x, y);
        rea[x] = true;
        rea[y] = true;
    }

    rea.resize(n);
    dfs(0, -1);

    set<int> comp;
    for (int i=0; i<n; i++) if (rea[i]) comp.insert(u.find(i));

    if (ssize(comp) > 1) cout << "Impossible\n";
    else cout << ans << '\n';
}
