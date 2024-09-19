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
	ll dsum = 0;
	for (ll x : holes) dsum += drev[x];

	sort(holes.begin(), holes.end(), [&](ll a, ll b) {
		return (w-2)*dadj[a] - drev[a] < (w-2)*dadj[b] - drev[b];
	});
	while(sz(holes) > 1'000) holes.pop_back();

	ll res = drev[0] * (w - 1);
	for (ll x : holes) {
		res = min(res, dsum - drev[x] + (w - 1) * dadj[x]);
	}

	ll g = gcd(res, w-1);
	cout << res/g << "/" << (w-1)/g << endl;
}
