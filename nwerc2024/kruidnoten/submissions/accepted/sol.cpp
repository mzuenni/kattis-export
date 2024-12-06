#include <bits/stdc++.h>
using namespace std;
using ll = long long;
const ll oo = 0x3f3f3f3f3f3f3f3fLL;

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout << fixed << setprecision(10);

	int n, m, k;
	cin >> n >> m >> k;
	vector<vector<pair<ll, int>>> g(n);
	for (ll i = 0; i < m; i++) {
		int a, b;
		ll w;
		cin >> a >> b >> w;
		a--; b--;
		g[a].emplace_back(w, b);
		g[b].emplace_back(w, a);
	}
	vector<int> A(k);
	vector<double> p(k);
	for (ll i = 0; i < k; i++) {
		cin >> A[i] >> p[i];
		A[i]--;
	}

	auto find_distances = [&](vector<ll> &d, int v) {
		priority_queue<pair<ll, int>, vector<pair<ll, int>>, greater<pair<ll, int>>> q;
		q.emplace(0, v);
		d[v] = 0;

		while (!q.empty()) {
			auto [c, v] = q.top();
			q.pop();
			if (d[v] < c) continue;
			for (auto [w, nxt]: g[v]) if (d[nxt] > c+w) {
				d[nxt] = c+w;
				q.emplace(c+w, nxt);
			}
		}
		return d;
	};

	vector<ll> d(n, oo), dr(n, oo);
	find_distances(d, 0);
	find_distances(dr, n-1);

	vector<ll> s(k);
	vector<int> o(k);
	for (ll i = 0; i < k; i++) s[i] = min(oo, d[A[i]]+dr[A[i]]);
	iota(o.begin(), o.end(), 0);
	sort(o.begin(), o.end(), [&](ll i, ll j){ return s[i] > s[j]; });

	ll def = oo;
	for (ll i = 0; i < k; i++) if (p[i] == 1.0) def = min(def, s[i]);
	if (def >= oo) {
		cout << "impossible" << endl;
		return 0;
	}

	double e = def;
	for (ll i = 0; i < k; i++) if (s[o[i]] < def) {
		e *= 1-p[o[i]];
		e += p[o[i]]*s[o[i]];
	}
	cout << e << endl;

	return 0;
}
