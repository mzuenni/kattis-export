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
    vector<vector<int>> ans;
    vector<int> rev(n);
    for (int i=0; i<n; i++) {
        if (a[i] != a2[i]) {
            addEdge(a[i], a2[i], i);
            rev[a[i]] = i;
        }
    }

    vector<int> comps;
    for (int i=0; i<n; i++) if (!adj[i].empty()) {
        euler(i);
        reverse(all(cycle));
        ans.push_back(cycle);
        cycle = {};
    }

    cout << ssize(ans) << '\n';
    for (auto vec : ans) {
        cout << ssize(vec) << '\n';
        for (int e : vec) cout << e+1 << ' ';
        cout << '\n';
    }
}
