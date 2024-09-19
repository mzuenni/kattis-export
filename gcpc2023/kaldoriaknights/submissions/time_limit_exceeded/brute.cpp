
#include <bits/stdc++.h>
using namespace std;

#define all(x) begin(x), end(x)
#define sz(x) (ll)(x).size()

using ll = long long;
using ld = long double;

constexpr ll mod = 1000000007;
vector<ll> fac(1000006);

bool isPerm(const vector<ll>& in, ll k) {
	for (ll i = 0; i < k; i++) if (in[i] >= k) return false;
	return true;
}

ll brute(ll n, const vector<ll>& s) {
	vector<ll> perm(n);
	iota(all(perm), 0);
	ll res = 0;
	do {
		bool ok = true;
		for (ll i = 0; i < sz(s); i++) {
			ok &= !isPerm(perm, s[i]);
		}
		if (ok) res++;
	} while(next_permutation(all(perm)));
	return res;
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
	cout << brute(n, s) << endl;
}
