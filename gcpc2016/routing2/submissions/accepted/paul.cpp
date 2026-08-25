#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef vector<ll> vl;
typedef pair<ll,ll> pll;
#define FOR(i,a,b) for (int i = (a); i < (b); i++)

int main() {
	ll n; cin >> n;
	vector<vector<pll>> adj(n*n);
	
	ll tlast;
	FOR(y,0,n) {
		ll m, t; cin >> m >> t;
		if (y == n-1) tlast = t;
		while (m--) {
			ll k, z; cin >> k >> z, z--;
			vl s(k);
			FOR(i,0,k) cin >> s[i], s[i]--;
			sort(begin(s),end(s));
			ll i = 0;
			FOR(x,0,n) if (i < k && s[i] == x) i++; else adj[n*x+y].push_back({t,n*y+z});
		}
	}
	
	vl d(n*n,1e12);
	set<pll> q;
	d[0] = 0, q.insert({0,0});
	while (!q.empty()) {
		ll i = begin(q)->second;
		q.erase(begin(q));
		if (i % n == n-1) {
			cout << d[i] + tlast << endl;
			return 0;
		}
		for (auto &e: adj[i]) {
			ll t, j; tie(t,j) = e;
			if (d[j] <= d[i] + t) continue;
			q.erase({d[j],j});
			d[j] = d[i] + t;
			q.insert({d[j],j});
		}
	}
	cout << "impossible" << endl;
}
