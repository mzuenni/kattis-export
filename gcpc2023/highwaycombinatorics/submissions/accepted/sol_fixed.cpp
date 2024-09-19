#include <bits/stdc++.h>
using namespace std;
 
#define all(x) begin(x), end(x)
#define sz(x) (ll)(x).size()
 
using ll = long long;
using ld = long double;

constexpr ll mod = 1000000007;
constexpr ll seed = 123456789;
constexpr ll lim = 200;

constexpr ll fibsLim = 24;
constexpr ll baseLim = 500000;

ll powMod(ll a, ll b = mod-2, ll n = mod) {
	ll res = 1;
	while (b > 0) {
		if (b & 1) res = (a * res) % n;
		a = (a * a) % n;
		b /= 2;
	}
	return res;
}

struct entry {
	ll val, ops;
	basic_string<ll> fibs;
	bool operator<(const entry& o) const {
		if(val != o.val) return val < o.val;
		if(ops != o.ops) return ops < o.ops;
		return false;
	}
	bool operator==(const entry& o) const {
		if(val != o.val) return false;
		if(ops != o.ops) return false;
		return true;
	}
};

vector<entry> fibs;
vector<entry> base;
mt19937 rng(seed);
void precalc() {
	ll f0 = 1;
	ll f1 = 1;
	for (ll i = 0; i < fibsLim; i++) {
		swap(f0, f1);
		f1 += f0;
		f1 %= mod;
		fibs.push_back({f1, i + 2, {i}});
	}
	base = fibs;
	for (ll l = 0, r = sz(base); r < baseLim; l = r, r = sz(base)) {
		for (ll i = l; i < r; i++) {
			for (ll j = base[i].fibs.back(); j < sz(fibs); j++) {
				entry e = base[i];
				e.val *= fibs[j].val;
				e.val %= mod;
				e.ops += fibs[j].ops + 1;
				e.fibs.push_back(j);
				if (e.ops <= lim) base.push_back(e);
			}
		}
	}
	sort(all(base));
	base.erase(unique(all(base)), base.end());
}

entry solve(ll x) {
	ll y = x % mod;
	entry res{1, 0, {}};
	while (res.ops < lim) {
		auto it = lower_bound(all(base), entry{y, 0, {}});
		if (it != base.end() && it->val == y) break;
		ll j = uniform_int_distribution<ll>(0, sz(fibs) - 1)(rng);

		y *= powMod(fibs[j].val);
		y %= mod;

		res.val *= fibs[j].val;
		res.val %= mod;
		res.ops += fibs[j].ops + 1;
		res.fibs.push_back(j);
	}
	if (res.ops < lim) {
		auto it = lower_bound(all(base), entry{y, 0, {}});
		res.val *= it->val;
		res.val %= mod;
		res.ops += it->ops;
		res.fibs += it->fibs;
	}
	if (res.ops >= lim) res = solve(x);
	return res;
}

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);

	precalc();
	ll x;
	cin >> x;
	if (x == 0) {
		cout << ".##" << endl;
		cout << "##." << endl;
	} else {
		entry e = solve(x);
		string res;
		for (ll x : e.fibs) {
			res += string(x + 2, '.');
			res += '#';
		}
		res.pop_back();

		cout << res << endl;
		cout << res << endl;
	}
}
