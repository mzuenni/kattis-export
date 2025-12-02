#include <bits/stdc++.h>
using namespace std;
using ll = long long;
#define all(x) ::begin(x), ::end(x)
#define debug(x) cerr << "[" << __LINE__ << "] "#x" = " << (x) << endl

vector<vector<pair<int, ll>>> g;
vector<int> par, jump, d, order;
vector<ll> w1, w2;
int counter = 0;
void init(int cur) {
    order[cur] = counter++;
    for (auto [e, z] : g[cur]) if (e != par[cur]) {
        par[e] = cur;
        w1[e] = w2[e] = z;
        d[e] = d[cur] + 1;
        if (d[jump[jump[cur]]] - d[jump[cur]] == d[jump[cur]] - d[cur]) {
            jump[e] = par[par[cur]];
            w2[e] += w2[par[cur]] + w2[cur];
        } else jump[e] = cur;
        init(e);
    }
}

pair<int, ll> up(int a, int height) {
    ll w = 0;
    while (d[a] > height) {
        if (d[jump[a]] >= height)  w += w2[a], a = jump[a];
        else w += w1[a], a = par[a];
    }
    return {a, w};
}

int lca(int a, int b) {
    if (d[a] < d[b]) swap(a, b);
    a = up(a, d[b]).first;
    while (a != b) {
        if (jump[a] != jump[b]) a = jump[a], b = jump[b];
        else a = par[a], b = par[b];
    }
    return a == b ? a : par[a];
}

unordered_map<int, int> mp;
vector<vector<pair<int, ll>>> g2;
int root;
void virt(vector<int>& a) {
    mp.clear();
    g2.clear();
    sort(all(a), [&](int x, int y){return order[x] < order[y];});

    vector<int> b;
    auto push = [&](int e) {
        if (!mp.contains(e)) mp[e] = mp.size(), g2.emplace_back();
        while (ssize(b) >= 2 && d[b.back()] > max(d[b.end()[-2]], d[e])) {
            auto [p, val] = up(b.back(), max(d[b.end()[-2]], d[e]));
            g2[mp[p]].emplace_back(mp[b.back()], val);
            b.pop_back();
        }
        if (b.empty() || e != b.back()) b.push_back(e);
    };

    for (int e : a) {
        if (!b.empty()) push(lca(b.back(), e));
        push(e);
    }

    root = b.back();
    for (int i=0; i<ssize(b)-1; i++) {
        if (d[b[i]] > d[b[i+1]]) {
            auto [p, val] = up(b[i], d[b[i+1]]);
            g2[mp[p]].emplace_back(mp[b[i]], val);
        } else {
            if (root == b.back()) root = b[i];
            auto [p, val] = up(b[i+1], d[b[i]]);
            g2[mp[p]].emplace_back(mp[b[i+1]], val);
        }
    }
    root = mp[root];
}


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
Union u(1);
vector<bool> rea;

ll ans = 0;
void dfs2(int cur) {
    for (auto [e, w] : g2[cur]) {
        dfs2(e);
        if (val[e]) u.join(cur, e), ans += w, rea[e] = true, rea[cur] = true;
        val[cur] ^= val[e];
    }
}

void solve() {
    int m;
    cin >> m;
    vector<int> relevant;
    vector<pair<int, int>> bridges(m);
    for (int i=0; i<m; i++) {
        int x, y;
        cin >> x >> y;
        x--, y--;
        bridges[i] = {x, y};
        relevant.push_back(x), relevant.push_back(y);
    }
    virt(relevant);

    int n = ssize(g2);

    u = Union(n);
    val.assign(n, 0);
    rea.assign(n, false);
    for (auto [x, y] : bridges) {
        x = mp[x], y = mp[y];
        val[x] ^= 1, val[y] ^= 1;
        u.join(x, y);
        rea[x] = true;
        rea[y] = true;
    }

    dfs2(root);

    set<int> comp;
    for (int i=0; i<n; i++) if (rea[i]) comp.insert(u.find(i));

    if (ssize(comp) > 1) cout << "Impossible\n";
    else cout << ans << '\n';
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

    par.assign(n, 0);
    jump.assign(n, 0);
    d.assign(n, 0);
    w1.assign(n, 0);
    w2.assign(n, 0);
    order.assign(n, -1);
    init(0);

    int q = 1;
    while (q--) {
        solve();
    }
}
