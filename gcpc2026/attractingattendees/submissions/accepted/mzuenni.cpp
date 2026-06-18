#include <bits/stdc++.h>
using namespace std;

#define all(x) begin(x), end(x)
#define sz(x) (ll)(x).size()

using ll = long long;
using ld = long double;

int main(int argc, char **argv) {
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);

	ll bands, fans, lim;
	cin >> bands >> fans >> lim;
	vector<vector<ll>> adj(bands+fans);
	for (ll i = 0; i < fans; i++) {
		ll k;
		cin >> k;
		for (ll j = 0; j < k; j++) {
			ll b;
			cin >> b;
			b--;
			adj[b].push_back(i+bands);
			adj[i+bands].push_back(b);
		}
	}
	vector<ll> deg(bands+fans);
	for (ll i = 0; i < bands+fans; i++) deg[i] = sz(adj[i]);

	auto remove = [&](ll i){
		if (deg[i] <= 0) return false;
		if (i < bands) {
			return deg[i] < lim;
		} else {
			return 2*deg[i] < sz(adj[i]);
		}
	};

	vector<ll> todo;
	for (ll i = 0; i < bands+fans; i++) {
		if (remove(i)) {
			todo.push_back(i);
			deg[i] = 0;
		}
	}

	while (!todo.empty()) {
		ll c = todo.back();
		todo.pop_back();
		for (ll x : adj[c]) {
			deg[x]--;
			if (remove(x)) {
				todo.push_back(x);
				deg[x] = 0;
			}
		}
	}

	vector<ll> res;
	for (ll i = 0; i < bands; i++) {
		if (deg[i] > 0) res.push_back(i);
	}

	if (res.empty()) {
		cout << "impossible" << endl;
	} else {
		cout << "possible" << endl;
		cout << sz(res) << endl;
		for (ll x : res) cout << x+1 << " ";
		cout << endl;
	}
}
