#include <bits/stdc++.h>
using namespace std;

#define all(x) begin(x), end(x)
#define sz(x) (ll)(x).size()

using ll = long long;
using ld = long double;

constexpr ll inf = 0x3FFFFFFFFFFFFFFF;

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);
	ll n, m;
	cin >> n >> m;
	vector<vector<pair<ll, ll>>> adj(n+1);
	for (ll i = 0; i < n; i++) {
		ll p;
		cin >> p;
		for (ll j = 1; j <= m && i+j <= n; j++) {
			ll x;
			cin >> x;
			adj[i].push_back({i+j, p-x});
		}
	}
	vector<ll> dist(n+1, inf);
	dist[0] = 0;
	priority_queue<pair<ll, ll>, vector<pair<ll, ll>>, greater<pair<ll, ll>>> todo;
	todo.push({0, 0});
	while (!todo.empty()) {
		ll d = todo.top().first;
		ll c = todo.top().second;
		todo.pop();
		if (d > dist[c]) continue;
		// it should be possible to pop a vertex multiple times due to negative edge lengths... => TLE
		for (auto [x, l] : adj[c]) {
			if (d+l < dist[x]) {
				dist[x] = d+l;
				todo.push({d+l, x});
			}
		}
	}

	cout << dist[n] << endl;
}
