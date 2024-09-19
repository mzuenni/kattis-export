#include <bits/stdc++.h>
using namespace std;
using i64 = long long;

__float128 sqrtq(__float128 x) {
	__float128 r = x;
	for (int i = 0; i < 10; i++) {
		r = 0.5 * (r + x/r);
	}
	return r;
}

const __float128 r2 = sqrtq(__float128(2));
const __float128 r3 = sqrtq(__float128(3));
const __float128 a1 = __float128(1) - __float128(1e-23);

// 0 = circle, 1 = square, 2 = triangle
const __float128 c[3][3] = {
	{a1, r2, r3},
	{a1/2, a1, 2*r2/(1+r3)},
	{0.5/r3, 3/(3+2*r3), a1}
};

i64 go(int i, int j, i64 n) {
	return n * c[i][j];
}

i64 grundy(int i, i64 n) {
	if (i == 0 && n == 1) return 2;
	return go(i, 2, n);
}

i64 inv_grundy(int i, i64 n) {
	if (i == 2) return n+1;
	if (i == 0 && n == 2) return 1;
	i64 m = ceill(n / c[i][2]);
	return grundy(i, m) == n ? m : 0;
}

int main() {
	int n; cin >> n;

	i64 G = 0;
	vector<i64> a(n), b(n), g(n);
	for (int i = 0; i < n; i++) {
		string s;
		cin >> s >> b[i];
		a[i] = s == "circle" ? 0 : s == "square" ? 1 : 2;
		g[i] = grundy(a[i], b[i]);
		G ^= g[i];
	}

	int res = 0;
	for (int i = 0; i < n; i++) {
		i64 x = g[i], y = G ^ g[i];
		if (y >= x) continue;
		for (int k = 0; k < 3; k++) {
			i64 nb = inv_grundy(k, y);
			res += nb != 0 && nb <= go(a[i], k, b[i]);
		}
	}
	cout << res << '\n';
}
