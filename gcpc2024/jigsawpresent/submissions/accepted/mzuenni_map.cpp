#include <bits/stdc++.h>
using namespace std;

#define all(x) begin(x), end(x)
#define sz(x) (ll)(x).size()

using ll = long long;
using ld = long double;

void yes(ll mask, ll submask) {
	cout << "NO" << endl;
	vector<ll> a, b;
	for (ll i = 1, j = 0; i <= mask; i*=2, j++) {
		if ((mask & i) == 0) continue;
		if ((submask & i) == 0) a.push_back(j);
		else b.push_back(j);
	}
	cout << sz(a);
	for (ll x : a) cout << " " << x+1;
	cout << endl;
	cout << sz(b);
	for (ll x : b) cout << " " << x+1;
	cout << endl;
}

template<typename F>
bool enumerate(const vector<ll>& in, int offset, int lim, F f) {
	vector<ll> sum(1 << lim);
	for (int i = 1; i < (1 << lim); i++) {
		int j = __builtin_ctzll(i);
		sum[i] = sum[i ^ (1 << j)] + in[j + offset];
	}
	for (int mask = 1; mask < (1 << lim); mask++) {
		for (int submask = mask; submask > 0; submask = (submask - 1) & mask) {
			ll x = sum[submask] - sum[submask ^ mask];
			if (x == 0) {
				yes(mask, submask);
				return true;
			}
			if (f(x, mask, submask)) return true;
		}
	}
	return false;
}

void solve(const vector<ll>& in) {
	unordered_map<ll, pair<int, int>> seen;
	ll m = sz(in) / 2;
	if (enumerate(in, 0, m, [&](ll id, int mask, int submask) {
		seen[id] = {mask, submask ^ mask};
		return false;
	})) return;
	ll m2 = sz(in) - m;
	if (enumerate(in, m, m2, [&](ll id, ll mask, ll submask) {
		auto it = seen.find(id);
		if (it == seen.end()) return false;
		yes(   (mask << m) | it->second.first,
			(submask << m) | it->second.second);
		return true;
	})) return;
	cout << "YES" << endl;
}

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);

	ll n;
	cin >> n;
	vector<ll> in(n);
	for (ll& z : in) {
		ll x, y;
		cin >> x >> y;
		z = (y << 19) | x;
	}
	if (n > 28) in.resize(28);
	solve(in);
}
