#include <bits/stdc++.h>
using ll = long long;
using namespace std;

int main(){
	cin.tie(0)->sync_with_stdio(false);
	int n;
	cin >> n;
	vector<vector<pair<int, ll>>> g(n);
	for(int i = 1; i < n; i++){
		int u, v; ll w;
		cin >> u >> v >> w;
		u--, v--;
		g[u].emplace_back(v, w);
		g[v].emplace_back(u, w);
	}
	int m;
	cin >> m;
	vector<int> a(n);
	for(int i = 0; i < m; i++){
		int u, v;
		cin >> u >> v;
		u--, v--;
		a[u] ^= 1;
		a[v] ^= 1;
	}
	ll ans = 0;
	auto dfs = [&](auto&& self, int u, int par) -> void {
		for(auto [v, w] : g[u]) if(v != par) {
			self(self, v, u);
			if(a[v]) ans += w, a[u] ^= 1; 
		}
	};
	dfs(dfs, 0, -1);
	cout << ans << "\n";
}