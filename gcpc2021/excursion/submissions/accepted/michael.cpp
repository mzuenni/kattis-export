#include <bits/stdc++.h>
using namespace std;

#define all(x) begin(x), end(x)
#define sz(x) (ll)(x).size()

using ll = long long;
using ld = long double;

constexpr ll lim = 1000007;
constexpr ll inf = 0x3FFFFFFF;

struct entry {
	ll id, d, t;
	bool operator<(const entry& o) const {
		return t < o.t;
	}
};

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);
	ll n, m;
	cin >> n >> m;
	vector<entry> in;
	for (ll i = 0; i < m; i++) {
		ll id, d, t;
		cin >> id >> d >> t;
		if (id+1 <= n) in.push_back({id, d, t});
	}
	sort(all(in));
	ll infs = n-1;
	ll cur = infs*inf;
	vector<ll> res(lim, cur), dist(n+1, inf);

	for (ll i = lim-1; i >= 0; i--) {
		while (!in.empty() && in.back().t >= i) {
			ll id = in.back().id;
			ll d = in.back().d;
			in.pop_back();

			if (dist[id] == inf) infs--;
			cur -= dist[id];
			dist[id] = min(dist[id], d);
			cur += dist[id];
			if (dist[id] == inf) infs++;
		}
		if (infs == 0) res[i] = cur;
	}

	ll q;
	cin >> q;
	for (ll i = 0; i < q; i++) {
		ll x;
		cin >> x;
		if (res[x] >= res.back()) {
			cout << "impossible" << endl;
		} else {
			cout << res[x] << endl;
		}
	}
}
