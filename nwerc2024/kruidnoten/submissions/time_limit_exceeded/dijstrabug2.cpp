#include <bits/stdc++.h>
using namespace std;

#define all(x) begin(x), end(x)
#define sz(x) (ll)(x).size()

using ll = long long;
using ld = long double;

constexpr ll INF = 0x3FFF'FFFF'FFFF'FFFF;

vector<ll> dijkstra(const vector<vector<pair<ll, ll>>>& adj, ll s) {
	vector<ll> dist(sz(adj), INF);
	dist[s] = 0;
	priority_queue<pair<ll, ll>/*, vector<pair<ll, ll>>, greater<pair<ll, ll>>*/> todo;
	todo.push({0, s});
	while (!todo.empty()) {
		auto [d, c] = todo.top();
		todo.pop();
		if (d != dist[c]) continue;
		for (auto [w, x] : adj[c]) {
			if (w + d < dist[x]) {
				dist[x] = w + d;
				todo.push({dist[x], x});
			}
		}
	}
	return dist;
}

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);
	ll n, m, k;
	cin >> n >> m >> k;
	vector<vector<pair<ll, ll>>> adj(n);
	for (ll i = 0; i < m; i++) {
		ll a, b, w;
		cin >> a >> b >> w;
		a--;
		b--;
		adj[a].push_back({w, b});
		adj[b].push_back({w, a});
	}
	vector<pair<ll, ld>> special(k);
	for (auto& [id, p] : special) cin >> id >> p, id--;
	auto dadj = dijkstra(adj, 0);
	auto drev = dijkstra(adj, n - 1);
	sort(all(special), [&](pair<ll, ld> a, pair<ll, ld> b){
		return dadj[a.first] + drev[a.first] < dadj[b.first] + drev[b.first];
	});
	ld res = 0;
	ld logPrev = log2l(1.0);
	bool ok = false;
	for (auto [id, p] : special) {
		res += exp2l(log2l(dadj[id] + drev[id]) + logPrev + log2(p));
		if (p >= 1.0) {
			ok = dadj[id] + drev[id] < INF;
			break;
		}
		logPrev += log2l(1 - p);
	}
	if (!ok) cout << "impossible" << endl;
	else cout << fixed << setprecision(20) << res << endl;
}
