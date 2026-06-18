#include <bits/stdc++.h>
#include <cassert>
using namespace std;
using ll = int64_t;
#define all(x) ::begin(x), ::end(x)
#define debug(x...) [](auto&& ...y){ cerr << "["#x"]:"; ((cerr << ' ' << y), ...) << endl; }(x)

vector<vector<pair<int, int>>> adj;
vector<int> cycle;

void addEdge(int u, int v, int val) {
	adj[u].emplace_back(v, val);
}

void euler(int v) {
	while (!adj[v].empty()) {
		auto [u, rev] = adj[v].back();
		adj[v].pop_back();
		euler(u);
        cycle.push_back(rev);
	}
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    int n;
    cin >> n;
    vector<int> a(n);
    for (int& e : a) cin >> e, e--;

    auto a2 = a;
    sort(all(a2));
    adj.resize(n);
    for (int it=0; it<2; it++) {
        vector<int> rev(n);
        for (int i=0; i<n; i++) {
            if (a[i] != a2[i]) {
                addEdge(a[i], a2[i], i);
                rev[a[i]] = i;
            }
        }

        vector<int> comps;
        cycle = {};
        for (int i=0; i<n; i++) if (!adj[i].empty()) {
            comps.push_back(rev[i]);
            euler(i);
        }
        reverse(all(cycle));

        if (comps.empty()) {
            assert(it == 0);
            cout << "0\n";
            return 0;
        }
        if (ssize(comps) == 1) {
            if (it == 0) cout << "1\n";
            cout << ssize(cycle) << '\n';
            for (int i=0; i<ssize(cycle); i++) {
                cout << cycle[i]+1 << " \n"[i == ssize(cycle)-1];
            }
            return 0;
        }

        auto a3 = a;
        for (int i=0; i<ssize(comps); i++) {
            a[comps[i]] = a3[comps[(i+1)%ssize(comps)]];
        }
        cout << "2\n";
        cout << ssize(comps) << '\n';
        for (int i=0; i<ssize(comps); i++) {
            cout << comps[i]+1 << " \n"[i == ssize(comps)-1];
        }
    }
    assert(false);
}
