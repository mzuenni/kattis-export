#include <bits/stdc++.h>
using namespace std;
#define all(x) (x).begin(), (x).end()
using ll = long long;

vector<int> par, siz;
int finds(int u){
	if(par[u] == u) return u;
	return par[u] = finds(par[u]);
}
void merg(int u, int v){
	u = finds(u), v = finds(v);
	if(u != v){
		par[u] = v;
		siz[v] += siz[u];
	}
}

int main(){
	int n, m;
	cin >> n >> m;
	vector<vector<int>> g(n);
	vector<int> state(n, -1);
	par.resize(n);
	iota(all(par), 0);
	siz.assign(n, 1);
	map<int, vector<pair<int, int>>> byT;
	for(int i = 0; i < m; i++){
		int u, v, t;
		cin >> u >> v >> t;
		u--, v--;
		byT[t].emplace_back(u, v);
	}
	ll ans = 0;
	for(auto [t, edges] : byT | views::reverse){
		set<int> verts;
		for(auto& [u, v] : edges){
			u = finds(u);
			v = finds(v);
			if(u == v){
				cout << "impossible\n";
				return 0;
			}
			verts.insert(u);
			verts.insert(v);
			g[u].push_back(v);
			g[v].push_back(u);
		}
		int cnt[2] = {0, 0};
		auto dfs = [&](auto&& self, int u) -> void {
			cnt[state[u]] += siz[u];
			for(int v : g[u]){
				if(state[v] == -1){
					state[v] = 1-state[u];
					self(self, v);
				}
				else if(state[v] == state[u]){
					cout << "impossible\n";
					exit(0);
				}
			}
		};
		for(int u : verts){
			if(state[u] == -1){
				state[u] = 0;
				cnt[0] = cnt[1] = 0;
				dfs(dfs, u);
				ans += min(cnt[0], cnt[1]);
			}
		}
		for(int u : verts){
			g[u].clear();
			state[u] = -1;
		}
		for(auto [u, v] : edges) merg(u, v);
	}
	cout << "possible\n" << ans << "\n";
}