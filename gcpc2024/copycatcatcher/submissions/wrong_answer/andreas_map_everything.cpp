#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const ll A = 53;
const ll B = 1000000007;
const ll maxn = 2500;
vector<ll> p;

bool matches(vector<ll> &a, vector<ll> &b) {
	// find b in a
	ll n = a.size();
	ll m = b.size();
	if (m > n) return false;

	if (b[m-1] == a[m-1]) return true;
	for (ll i = 1; i < n - m + 1; i++) {
		if (b[m-1] == (a[i+m-1] - a[i-1]*p[m]) % B) return true;
	}
	return false;
}

vector<ll> h(vector<ll> a) {
	ll n = a.size();

	vector<ll> res(n);
	res[0] = a[0];
	for (ll i = 1; i < n; i++)
		res[i] = (res[i-1]*A + a[i]) % B;

	return res;
}

vector<ll> read_string() {
	ll n; cin >> n;

	map<string, ll> lst;
	vector<ll> t(n);
	for (ll i = 0; i < n; i++) {
		string s; cin >> s;
		if (lst.find(s) == lst.end()) {
			t[i] = 0;
		} else {
			t[i] = i - lst[s];
		}
		lst[s] = i;
	}
	return h(t);
}

int main() {
	cin.tie(0);
	ios_base::sync_with_stdio(0);

	p.assign(maxn, 1LL);
	for (ll i = 1; i < maxn; i++)
		p[i] = p[i-1]*A % B;

	vector<ll> s = read_string();

	ll q; cin >> q;
	while (q--) {
		vector<ll> t = read_string();
		cout << (matches(s, t) ? "yes\n" : "no\n");
	}

	return 0;
}
