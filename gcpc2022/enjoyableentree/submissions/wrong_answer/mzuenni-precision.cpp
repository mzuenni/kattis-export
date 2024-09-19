#include <bits/stdc++.h>
using namespace std;

#define all(x) begin(x), end(x)
#define sz(x) (ll)(x).size()

using ll = long long;
using ld = long double;

struct mat {
	ld a, b, c, d;
	mat() : a(0.5), b(0.5), c(1), d(0) {}
	mat(ld x) : a(x), b(0), c(0), d(x) {}

	mat operator*(const mat& o) const {
		mat res;
		res.a = a*o.a+b*o.c;
		res.b = a*o.b+b*o.d;
		res.c = c*o.a+d*o.c;
		res.d = c*o.b+d*o.d;
		return res;
	}
};

mat powMod(mat a, ll b) {
	mat res(1);
	while (b > 0) {
		if (b & 1) res = a * res;
		a = a * a;
		b /= 2;
	}
	return res;
}


int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);
	ll n;
	cin >> n;
	ld y, z;
	if (n == 1) {
		y = 100;
		z = 0;
	} else if (n == 2) {
		y = 0;
		z = 100;
	} else {
		mat x = powMod(mat(), n-2);
		y = 100*x.b;
		z = 100*x.a;
	}
	cout << fixed << setprecision(10) << y << " " << z << endl;
}
