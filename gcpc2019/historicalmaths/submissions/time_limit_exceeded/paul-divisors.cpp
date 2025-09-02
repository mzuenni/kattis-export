#include <bits/stdc++.h>
using namespace std;

int Bmin = 2;

vector<int> read_poly() {
	int n; cin >> n;
	vector<int> a(n);
	for (int i = 0; i < n; i++) cin >> a[i];
	reverse(begin(a),end(a));
	Bmin = max(Bmin, *max_element(begin(a),end(a)) + 1);
	return a;
}

long long find_base() {
	vector<int> a = read_poly();
	vector<int> b = read_poly();
	vector<int> c = read_poly();
	if (c.size() + 1 < a.size() + b.size()) return -1;

	vector<__int128> ab(c.size());
	for (int i = 0; i < (int)a.size(); i++) {
		for (int j = 0; j < (int)b.size(); j++) {
			ab[i+j] += __int128(a[i]) * b[j];
		}
	}
	
	int k = 0; // position of first carry
	while (k < (int)c.size() && ab[k] == c[k]) k++;
	if (k == (int)c.size()) return Bmin;
	
	__int128 Bmult = ab[k] - c[k];
	if (Bmult < 0) return -1;

	auto try_base = [&](__int128 B) {
		if (B < Bmin || B > LLONG_MAX) return false;
		__int128 carry = 0;
		for (int i = k; i < (int)c.size(); i++) {
			carry += ab[i];
			if (carry % B != c[i]) return false;
			carry /= B;
		}
		return carry == 0;
	};

	for (__int128 B = 1; B*B <= Bmult; B++) if (Bmult%B == 0) {
		if (try_base(B)) return B;
		if (try_base(Bmult/B)) return Bmult/B;
	}
	return -1;
}

int main() {
	long long res = find_base();
	if (res != -1) cout << res << endl;
	else cout << "impossible" << endl;
}
