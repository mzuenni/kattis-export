//greedy solution, could be WA

#include <bits/stdc++.h>
using namespace std;

#define all(x) begin(x), end(x)
#define sz(x) (ll)(x).size()

using ll = long long;
using ld = long double;

constexpr ll inf = 0x3FFFFFFFFF;

void solve(ll x) {
	if (x <= 0) {
		cout << "impossible" << endl;
	} else {
		cout << x << endl;
	}
	exit(0);
}

struct event {
	ll pos, type, id, l, r;
	bool operator<(const event& o) const {
		if (pos != o.pos) return pos < o.pos;
		return type < o.type;
	}
};

vector<ll> domset(vector<event>& in) {
	sort(all(in));
	vector<ll> res;
	ll covered = -inf;
	pair<ll, ll> cur = {-inf, -1};
	bool required = false;
	for (auto e : in) {
		if (e.type > 0) {
			cur = max(cur, {e.r, e.id});
			required |= e.l >= covered;
		} else {
			if (e.l >= covered) {
				res.push_back(cur.second);
				covered = cur.first;
				cur = {-inf, -1};
				required = false;
			}
		}
	}
	if (required) res.push_back(cur.second);
	return res;
}

vector<ll> extension(vector<event>& in) {
	vector<ll> res(sz(in) / 2);
	pair<ll, ll> cur = {-inf, -1};
	for (auto e : in) {
		if (e.type > 0) {
			cur = max(cur, {e.r, e.id});
		} else {
			res[e.id] = cur.second;
		}
	}
	return res;
}

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);
	ll n;
	cin >> n;
	vector<event> lr, rl;
	vector<pair<ll, ll>> in(n);
	for (ll i = 0; i < n; i++) {
		ll l, r;
		cin >> l >> r;
		in[i] = {l, r};
		lr.push_back({  l,  1, i,  l, 1+r});
		lr.push_back({1+r, -1, i,  l, 1+r});
		rl.push_back({ -r,  1, i, -r, 1-l});
		rl.push_back({1-l, -1, i, -r, 1-l});
	}
	auto dlr = domset(lr);
	if (sz(dlr) <= 1) solve(-1);
	auto drl = domset(rl);
	reverse(all(drl));

	auto tmp = extension(lr);

	ll res = 3;
	for (ll i = 0; i+1 < sz(dlr); i++) {
		if (res > 1 && in[drl[i+1]].first <= in[dlr[i]].second) res = 1;
		if (res > 2 && in[drl[i+1]].first <= in[tmp[dlr[i]]].second) res = 2;
	}
	solve(res);
}
