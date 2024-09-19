#include <bits/stdc++.h>
using namespace std;

#define all(x) begin(x), end(x)
#define sz(x) (ll)(x).size()

using ll = long long;
using ld = long double;

vector<vector<ll>> adj;

vector<ll> bfs(ll x) {
	vector<ll> dist(sz(adj), -1);
	dist[x] = 0;
	queue<ll> todo;
	todo.push(x);
	while (!todo.empty()) {
		ll c = todo.front();
		todo.pop();
		for (ll y : adj[c]) {
			if (dist[y] < 0) {
				dist[y] = dist[c] + 1;
				todo.push(y);
			}
		}
	}
	return dist;
}

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);
	ll n, m, w;
	cin >> n >> m >> w;
	assert(w >= 2); //1 makes no sense, where would you end?
	vector<ll> holes(w);
	for (ll& x : holes) cin >> x, x--;
	adj.assign(n, {});
	for (ll i = 0; i < m; i++) {
		ll a, b;
		cin >> a >> b;
		a--;
		b--;
		adj[a].push_back(b);
		adj[b].push_back(a);
	}
	auto dadj = bfs(0);
	auto drev = bfs(n - 1);
	ll best = holes[0];
	for (ll x : holes) {
		if ((w-1) * dadj[x] - drev[x] < (w-1) * dadj[best] - drev[best]) best = x;
	}
	ll res = 0;
	for (ll x : holes) {
		if (x != best) res += dadj[best] + drev[x];
	}
	res = min(res, drev[0] * (w - 1));
	ll g = gcd(res, w-1);
	cout << res/g << "/" << (w-1)/g << endl;
}
