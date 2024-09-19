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
	vector<vector<ll>> adj(n);
	for (ll i = 0; i < m; i++) {
		ll a, b;
		cin >> a >> b;
		a--, b--;
		adj[a].push_back(b);
		adj[b].push_back(a);
	}
	
	ll res = 0;
	//stupid way to find 0.5...
	for (ll i = 0; i < p; i++) if ((2*i % p) == 1) res = i;
	vector<ll> seen(n, -1);
	for (ll i = 0; i < n; i++) {
		if (seen[i] < 0) {
			res *= 2;
			res %= p;
			seen[i] = 0;
			vector<ll> stack = {i};
			while (!stack.empty()) {
				ll cur = stack.back();
				stack.pop_back();
				for (ll x : adj[cur]) {
					if (seen[x] < 0) {
						seen[x] = seen[cur] ^ 1;
						stack.push_back(x);
					} else if (seen[x] != (seen[cur] ^ 1)) {
						cout << "impossible" << endl;
						return 0;
					}
				}
			}
		}
	}
	res++;
	res %= p;
	cout << res << endl;
}
