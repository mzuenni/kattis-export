#include <bits/stdc++.h>
using namespace std;

#define all(x) begin(x), end(x)
#define sz(x) (ll)(x).size()

using ll = long long;
using ld = long double;

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);
	ll w, h;
	cin >> h >> w;
	vector<vector<ll>> todo(h);
	for (ll i = 0; i < h; i++) {
		for (ll j = 0; j < w; j++) {
			char c;
			cin >> c;
			if (c == 'C') todo[i].push_back(j);
		}
	}

	ll res = 0;
	for (ll i = 0; i < h; i++) {
		if (todo[i].empty()) continue;
		res++;
		ll lim = todo[i].back();
		todo[i].clear();
		for (ll j = i + 1; j < h; j++) {
			ll oldLim = lim;
			while (!todo[j].empty() && todo[j].back() >= oldLim) {
				lim = max(lim, todo[j].back());
				todo[j].pop_back();
			}
		}
	}
	cout << res << endl;
}
