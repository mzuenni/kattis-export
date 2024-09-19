#include <bits/stdc++.h>
using namespace std;

#define all(x) begin(x), end(x)
#define sz(x) (ll)(x).size()

using ll = long long;
using lll = __int128;
using ld = long double;

array<ll, 5> val = {4,6,8,12,20};

vector<lll> conv(const vector<lll>& a, ll vb) {//this should overflow!
	vector<lll> res(sz(a));
	for (ll i = 0; i + val.back() < sz(a); i++) {
		for (ll j = 1; j <= vb; j++) {
			res[i+j] += a[i];
		}
	}
	return res;
}

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);

	vector<ll> in(sz(val));
	for (ll& x : in) cin >> x;

	vector<lll> count(val.back()*10*sz(val)+val.back());
	count[0] = 1;
	for (ll i = 0; i < sz(in); i++) {
		for (ll j = 0; j < in[i]; j++) {
			count = conv(count, val[i]);
		}
	}

	map<lll, vector<ll>, greater<ll>> res;
	for (ll i = 0; i < sz(count); i++) {
		if (count[i] > 0) res[count[i]].push_back(i);
	}

	for (auto& [_, v]: res) {
		for (ll x : v) cout << x << " ";
	}
	cout << endl;
}
