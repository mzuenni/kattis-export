#include <bits/stdc++.h>
using namespace std;

#define all(x) begin(x), end(x)
#define sz(x) (ll)(x).size()

using ll = long long;
using ld = long double;

constexpr ll mod = 1000000007;
vector<ll> fac(1000006);

ll solve(ll n, vector<ll> s) {//s strictly increasing!
	s.push_back(n);
	vector<ll> tmp(sz(s));// #perms with first error at s[i] and length cur iteration
	for (ll i = 0; i < sz(s); i++) {
		tmp[i] = fac[s[i]];
		for (ll j = 0; j < i; j++) {
			ll x = (tmp[j] * fac[s[i] - s[j]]) % mod;
			tmp[i] += mod - x;
		}
		tmp[i] %= mod;
	}
	return tmp.back();
}

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);
	fac[0] = 1;
	for (ll i = 1; i < sz(fac); i++) fac[i] = (fac[i-1] * i) % mod;

	ll n, k;
	cin >> n >> k;
	vector<ll> s(k);
	ll sum = 0;
	for (ll& x : s) {
		cin >> x;
        ll psum = sum;
        sum += x;
        x += psum;
	}
	cout << solve(n, s) << endl;
}
