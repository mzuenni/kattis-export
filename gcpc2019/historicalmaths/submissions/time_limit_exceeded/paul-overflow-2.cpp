#include <bits/stdc++.h>
using namespace std;
using ll = long long;

vector<ll> multiply(vector<ll> a, vector<ll> b, ll B) {
	vector<ll> c(a.size() + b.size());
	for (int i = 0; i < int(a.size()); i++) {
		for (int j = 0; j < int(b.size()); j++) {
			c[i+j] += a[i]*b[j];
			if (c[i+j] >= B) {
				c[i+j+1] += c[i+j]/B;
				c[i+j] %= B;
			}
		}
	}
	while (c.back() == 0) c.pop_back();
	return c;
}

bool less_than(vector<ll> a, vector<ll> b) {
	if (a.size() != b.size()) return a.size() < b.size();
	for (int i = a.size()-1; i >= 0; i--) if (a[i] != b[i]) return a[i] < b[i];
	return false;
}

vector<ll> read_poly() {
	int n; cin >> n;
	vector<ll> a(n);
	for (int i = 0; i < n; i++) cin >> a[i];
	reverse(begin(a),end(a));
	return a;
}

int main() {
	vector<ll> a = read_poly(), b = read_poly(), c = read_poly();
	
	ll Bmin = 0, Bmax = 5e18;
	for (auto &p: {a,b,c}) Bmin = max(Bmin, *max_element(begin(p),end(p)) + 1);
	
	while (Bmin <= Bmax) {
		ll B = (Bmin+Bmax)/2;
		vector<ll> ab = multiply(a,b,B);
		if (ab == c) {
			cout << B << endl;
			return 0;
		}
		if (less_than(ab,c)) Bmax = B-1;
		else Bmin = B+1;
	}
	cout << "impossible" << endl;
}
