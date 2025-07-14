#include <bits/stdc++.h>
using namespace std;

using ll = int64_t;
using pll = pair<ll, ll>;

#define TS ll ts; cin >> ts; while (ts--)
#define all(x) ::begin(x), ::end(x)
constexpr ll INF = 1e18;

ll n, m;
vector<vector<ll>> adj;
ll s, t;

vector<ll> vis;
void dfs(ll c, ll x) {
	if (vis[c] >= x) return;
	vis[c] += x;

	for (ll u : adj[c]) {
		dfs(u, x);
	}
}

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	
	cin >> n >> m;
	adj.resize(n);
	for (ll i = 0; i < m; ++i) {
		ll u, v;
		cin >> u >> v;
		--u; --v;

		adj[u].push_back(v);
	}
	cin >> s >> t;
	--s; --t;

	vis.resize(n, 0);
	dfs(s, 1);
	dfs(t, 2);

	ll res = -1;
	for (ll i = 0; i < n; ++i) {
		if (vis[i] == 3) {
			res = i;
			break;
		}
	}

	if (res == -1) cout << "no\n";
	else {
		cout << "yes\n";
		cout << (res + 1) << '\n';
	}
	
	return 0;
}
