#include <bits/stdc++.h>
using namespace std;
using ll = long long;
#define all(x) ::begin(x), ::end(x)
void _d(auto... x) { ((cerr << ' ' << x), ...) << endl; }
#define debug(x...) cerr << "["#x"]:", _d(x)

vector<vector<pair<int, ll>>> g;
vector<int> par, jump, d, in, out;
vector<ll> w1, w2;
int counter = 0;
void init(int cur) {
    in[cur] = counter++;
    for (auto [e, z] : g[cur]) if (e != par[cur]) {
        par[e] = cur;
        w1[e] = w2[e] = z;
        d[e] = d[cur] + 1;
        if (d[jump[jump[cur]]] - d[jump[cur]] == d[jump[cur]] - d[cur]) {
            jump[e] = jump[jump[cur]];
            w2[e] += w2[jump[cur]] + w2[cur];
        } else jump[e] = cur;
        init(e);
    }
    out[cur] = counter;
}

pair<int, ll> up(int a, int height) {
    ll w = 0;
    while (d[a] > height) {
        if (d[jump[a]] >= height) w += w2[a], a = jump[a];
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

bool comp(int x, int y) {
    return in[x] < in[y];
}

ll virtualTree(vector<int> ind) {
    auto a = ind;
	sort(all(ind), comp);
	for (int i = 1, n = ssize(ind); i < n; i++) {
		ind.push_back(lca(ind[i - 1], ind[i]));
	}
	sort(all(ind), [&](int x, int y) {return in[x] < in[y];});
	ind.erase(unique(all(ind)), ind.end());

	int n = ssize(ind);
	vector<vector<pair<int, ll>>> tree(n);
	vector<int> st = {0};
	for (int i = 1; i < n; i++) {
		while (in[ind[i]] >= out[ind[st.back()]]) st.pop_back();
		tree[st.back()].emplace_back(i, up(ind[i], d[ind[st.back()]]).second);
		st.push_back(i);
	}

    vector<char> val(n);
    for (int& e : a) e = lower_bound(all(ind), e, comp) - ind.begin();
    for (int e : a) val[e] ^= 1;

    Union un(n);
    ll ans = 0;
    for (int i=n-1; i>=0; i--) {
        for (auto [v, w] : tree[i]) {
            val[i] ^= val[v];
            if (val[v]) ans += w, un.join(i, v);
        }
    }

    for (int i=0; i<ssize(a); i+=2) un.join(a[i], a[i+1]);

    int x = un.find(a[0]);
    for (int e : a) {
        if (un.find(e) != x) return -1;
    }

    return ans;
}


void solve() {
    int m;
    cin >> m;
    vector<int> relevant;
    for (int i=0; i<m; i++) {
        int x, y;
        cin >> x >> y;
        x--, y--;
        relevant.push_back(x), relevant.push_back(y);
    }
    ll ans = virtualTree(relevant);

    if (ans == -1) cout << "Impossible\n";
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
    jump = d = in = out = par;
    w1.assign(n, 0);
    w2 = w1;
    init(0);

    int q = 1;//change this
    while (q--) {
        solve();
    }
}
