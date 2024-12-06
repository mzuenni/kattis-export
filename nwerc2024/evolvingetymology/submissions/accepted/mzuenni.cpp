#include <bits/stdc++.h>
using namespace std;

#define all(x) begin(x), end(x)
#define sz(x) (ll)(x).size()

using ll = long long;
using ld = long double;

vector<ll> applyPerm(const vector<ll>& a, const vector<ll>& b) {
	vector<ll> res(sz(a));
	for (ll i = 0; i < sz(a); i++) res[i] = b[a[i]];
	return res;
}

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);

	ll n, k;
	string s;
	cin >> n >> k >> s;
	vector<ll> perm(n);
	for (ll i = 0; i < n; i++) perm[i] = (2 * i) % n;

	vector<ll> res(n);
	iota(all(res), 0);
	while (k > 0) {
		if (k & 1) res = applyPerm(perm, res);
		perm = applyPerm(perm, perm);
		k /= 2;
	}

	for (ll i = 0; i < n; i++) cout << s[res[i]];
	cout << endl;
}

//delftdelft
//d l t e f
//dltefdltef
//d t f l e
