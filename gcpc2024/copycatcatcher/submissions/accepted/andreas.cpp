#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const ll A = 53;
const ll B = 1000000007;
const ll maxn = 2500;
vector<ll> p;
map<string, ll> id_of_const;
ll maxcid = maxn;

bool matches(vector<vector<ll>> &a, vector<ll> &b) {
	// find b in a
	ll n = a.size();
	ll m = b.size();
	if (m > n) return false;

	for (ll i = 0; i < n - m + 1; i++) {
		if (b[m-1] == a[i][m-1]) return true;
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

vector<ll> parse(ll n, vector<string> &s, ll j) {
	map<string, ll> lst;
	vector<ll> t(n-j);
	for (ll i = j; i < n; i++) {
		if (s[i].size() == 1 && isalpha(s[i][0])) {
			if (lst.find(s[i]) == lst.end()) {
				t[i-j] = 0;
			} else {
				t[i-j] = i - lst[s[i]];
			}
			lst[s[i]] = i;
		} else {
			if (id_of_const.find(s[i]) == id_of_const.end())
				id_of_const[s[i]] = maxcid++;
			t[i-j] = id_of_const[s[i]];
		}
	}
	return t;
}

vector<vector<ll>> read_string(bool ref = false) {
	ll n; cin >> n;
	vector<string> s(n);
	for (ll i = 0; i < n; i++) cin >> s[i];

	vector<vector<ll>> res;
	res.push_back(parse(n, s, 0));
	if (ref) for (ll j = 1; j < n; j++) res.push_back(parse(n, s, j));

	for (auto &t: res) t = h(t);
	return res;
}

int main() {
	cin.tie(0);
	ios_base::sync_with_stdio(0);

	p.assign(maxn, 1LL);
	for (ll i = 1; i < maxn; i++)
		p[i] = p[i-1]*A % B;

	vector<vector<ll>> s = read_string(true);

	ll q; cin >> q;
	while (q--) {
		vector<ll> t = read_string()[0];
		cout << (matches(s, t) ? "yes\n" : "no\n");
	}

	return 0;
}
