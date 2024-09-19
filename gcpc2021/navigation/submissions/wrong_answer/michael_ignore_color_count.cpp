#include <bits/stdc++.h>
using namespace std;
 
#define all(x) begin(x), end(x)
#define sz(x) (int)(x).size()
 
using ll = long long;
using ld = long double;

constexpr ll inf = 0x3FFFFFFFFFFFFFF;

struct edge {
	ll from, dist, color;
};

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);
	ll n, m, k;
	cin >> n >> m >> k;
	vector<vector<edge>> rev(n);
	vector<map<ll, ll>> colorCount(n);
	for (ll i = 0; i < m; i++) {
		ll a, b, c;
		cin >> a >> b >> c;
		a--;
		b--;
		ll l;
		cin >> l;
		for (ll j = 0; j < l; j++) {
			ll li;
			cin >> li;
			rev[b].push_back({a, c, li});
			colorCount[a][li]++;
		}
	}
	vector<ll> dists(n, inf);
	vector<map<ll, ll>> distByColor(n);
	priority_queue<pair<ll, ll>, vector<pair<ll, ll>>, greater<pair<ll, ll>>> pq;
	pq.push({0, n-1});
	dists[n-1] = 0;
	while (!pq.empty()) {
		ll d = pq.top().first;
		ll x = pq.top().second;
		pq.pop();
		if (d != dists[x]) continue;
		for (auto e : rev[x]) {
			ll newDist = e.dist + d;
			distByColor[e.from][e.color] = max(distByColor[e.from][e.color], newDist);
			colorCount[e.from][e.color]--;
			//if (colorCount[e.from][e.color] == 0) {
				newDist = distByColor[e.from][e.color];
				if (newDist < dists[e.from]) {
					dists[e.from] = newDist;
					pq.push({newDist, e.from});
				}
			//}
		}
	}
	if (dists[0] < inf) {
		cout << dists[0] << endl;
	} else {
		cout << "impossible" << endl;
	}
}
