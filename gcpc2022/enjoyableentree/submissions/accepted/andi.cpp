#include <bits/stdc++.h>
using namespace std;

vector<vector<double>> mult(vector<vector<double>> a, vector<vector<double>> b) {
	return vector<vector<double>>{ { a[0][0] * b[0][0] + a[0][1] * b[1][0], a[0][0] * b[0][1] + a[0][1] * b[1][1] },
		{ a[1][0] * b[0][0] + a[1][1] * b[1][0], a[1][0] * b[0][1] + a[1][1] * b[1][1] } };
}

vector<vector<double>> fexp(vector<vector<double>> m, int64_t n) {
	if (n == 0) return vector<vector<double>>{ { 1, 0 }, { 0, 1 } };
	vector<vector<double>> k = fexp(m, n / 2);
	k = mult(k, k);
	if (n & 1) k = mult(k, m);
	return k;
}

pair<double, double> solve(int64_t n) {
	if (n == 1) return make_pair(100.0, 0);
	if (n == 2) return make_pair(0, 100.0);
	n -= 2;
	vector<vector<double>> m = { { 0, 1 }, { 0.5, 0.5 } };
	m = fexp(m, n);
	return make_pair(m[1][0] * 100, m[1][1] * 100);
}

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout << fixed << setprecision(10);
	
	int64_t n; cin >> n;
	auto [a,b] = solve(n);
	cout << a << ' ' << b << '\n';

	return 0;
}
