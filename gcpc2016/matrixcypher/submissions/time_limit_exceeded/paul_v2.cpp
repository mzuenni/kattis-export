#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef vector<ll> vl;
#define sz(c) ll((c).size())
#define FOR(i,a,b) for (ll i = (a); i < (b); i++)

vl operator-(const vl &a, const vl &b) {
	vl c;
	ll carry = 0;
	FOR(i,0,sz(a)) {
		if (i < sz(b)) carry += b[i];
		if (carry > a[i]) c.push_back(10+a[i]-carry), carry = 1;
		else c.push_back(a[i]-carry), carry = 0;
	}
	while (sz(c) && !c.back()) c.pop_back();
	return c;
}

bool operator<(const vl &a, const vl &b) {
	if (sz(a) != sz(b)) return sz(a) < sz(b);
	return lexicographical_compare(a.rbegin(),a.rend(),b.rbegin(),b.rend());
}

vl read() {
	string s; cin >> s;
	reverse(begin(s),end(s));
	vl res;
	for (char c : s) res.push_back(c-'0');
	return res;
}

const vl one = {1}, zero = {};

int main() {
	vl a = read(), b = read(), c = read(), d = read();
	vector<bool> res;
	while (a != one || b != zero || c != zero || d != one) {
		if (b < a) a = a-b, c = c-d, res.push_back(0);
		else b = b-a, d = d-c, res.push_back(1);
	}
	reverse(begin(res),end(res));
	char x = 0;
	FOR(i,0,sz(res)) {
		cout << res[i];
	}
	cout << endl;
}


