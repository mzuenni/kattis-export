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
	vector<ll> deg(bands+fans), active(bands+fans);
	for (ll i = 0; i < bands+fans; i++) {
		deg[i] = sz(adj[i]);
		active[i] = i;
	}

	auto remove = [&](ll i){
		if (deg[i] <= 0) return false;
		if (i < bands) {
			return deg[i] < lim;
		} else {
			return 2*deg[i] < sz(adj[i]);
		}
	};

	mt19937_64 rng(chrono::high_resolution_clock::now().time_since_epoch().count());
	shuffle(all(active), rng);

	bool changed;
	do {
		changed = false;
		for (ll i = 0; i < sz(active);) {
			ll c = active[i];
			if (remove(c)) {
				deg[c] = 0;
				for (ll x : adj[c]) deg[x]--;
				changed = true;
				swap(active[i], active.back());
				active.pop_back();
				break;
			} else {
				i++;
			}
		}
	} while (changed);

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
