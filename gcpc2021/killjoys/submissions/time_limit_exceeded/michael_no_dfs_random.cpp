#include <bits/stdc++.h>
using namespace std;

#define all(x) begin(x), end(x)
#define sz(x) (ll)(x).size()

using ll = long long;
using ld = long double;

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);
	ll n, m, p;
	cin >> n >> m >> p;
	vector<pair<ll, ll>> edges;
	for (ll i = 0; i < m; i++) {
		ll a, b;
		cin >> a >> b;
		a--, b--;
		edges.push_back({a, b});
	}
	ll c = 0;
	vector<ll> seen(n, -1);
	for (ll i = 0; i < n; i++) {
		if (seen[i] < 0) {
			c++;
			seen[i] = 0;
			while (true) {
				bool updated = false;
				for (ll j = 0; j < sz(edges); j++) {
					if (seen[edges[j].first] >= 0 &&
						seen[edges[j].second] >= 0) {
						if (seen[edges[j].first] == seen[edges[j].second]) {
							cout << "impossible" << endl;
							return 0;
						}
						swap(edges[j], edges.back());
						edges.pop_back();
						j--;
						updated = true;
					} else if (seen[edges[j].first] >= 0) {
						seen[edges[j].second] = seen[edges[j].first] ^ 1;
						swap(edges[j], edges.back());
						edges.pop_back();
						j--;
						updated = true;
					} else if (seen[edges[j].second] >= 0) {
						seen[edges[j].first] = seen[edges[j].second] ^ 1;
						swap(edges[j], edges.back());
						edges.pop_back();
						j--;
						updated = true;
					}
				}
				if (!updated) break;
			}
		}
	}
	ll res = 1;
	for (ll i = 1; i < c; i++) {
		res *= 2;
		res %= p;
	}
	res++;
	res %= p;
	cout << res << endl;
}
