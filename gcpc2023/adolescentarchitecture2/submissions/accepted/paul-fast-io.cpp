#include <bits/stdc++.h>
using namespace std;
using i64 = long long;

// 0 = circle, 1 = square, 2 = triangle
const long double c[3][3] = {
	{1, sqrtl(2), sqrtl(3)},
	{0.5, 1, 2*sqrtl(2)/(1+sqrtl(3))},
	{0.5/sqrtl(3), 3/(3+2*sqrtl(3)), 1}
};

i64 go(int i, int j, i64 n) {
	return n * c[i][j] * (1.L - 5e-19);
}

i64 grundy(int i, i64 n) {
	if (i == 0 && n == 1) return 2;
	return go(i, 2, n);
}

i64 inv_grundy(int i, i64 n) {
	if (i == 2) return n+1;
	if (i == 0 && n == 2) return 1;
	i64 m = ceill(n / c[i][2] * (1.L + 5e-19));
	return grundy(i, m) == n ? m : 0;
}

int main() {
	cin.tie(0)->sync_with_stdio(0);
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
