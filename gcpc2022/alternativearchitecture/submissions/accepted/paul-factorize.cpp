#include <bits/stdc++.h>
using namespace std;
using i64 = long long;

i64 exp_mod(i64 a, i64 n, i64 m) {
	__int128 res = 1 % m;
	while (n) {
		if (n%2) res = res*a % m;
		a = __int128(a)*a % m;
		n /= 2;
	}
	return res;
}

i64 inv_mod(i64 a, i64 m) { return exp_mod(a, m-2, m); }

bool witness(i64 a, i64 n) {
	i64 u = n-1, t = 0;
	for (; u % 2 == 0; u /= 2) t++;
	i64 v1 = exp_mod(a,u,n), v2 = n-1;
	while (v1 != 1 && t--) tie(v1,v2) = make_pair(__int128(v1)*v1 % n, v1);
	return v1 != 1 || v2 != n-1;
}

i64 v[] = {2, 325, 9375, 28178, 450775, 9780504, 1795265022};
bool is_prime(i64 n) {
	if (n <= 1) return false;
	if (n == 2) return true;
	if (n % 2 == 0) return false;
	for (i64 a: v) if (a % n && witness(a,n)) return false;
	return true;
}

mt19937_64 gen(2323845);
uniform_int_distribution<i64> dis(0,1e18);

i64 rho(i64 n) {
	i64 x, y, i = 1, k = 2, d, a;
	x = y = dis(gen) % n, a = dis(gen) % n;
	while (true) {
		++i;
		x = (__int128(x)*x + a) % n;
		if (x == y) return 0;
		d = gcd(abs(x-y),n);
		if (d != 1) return d;
		if (i == k) y = x, k *= 2;
	}
	return 0;
}

map<i64,i64> factorize(i64 n) {
	if (n == 1) return {};
	
	map<i64,i64> fac;
	queue<i64> q;
	q.push(n);
	while (!q.empty()) {
		i64 m = q.front(); q.pop();
		if (is_prime(m)) {
			fac[m]++;
			continue;
		}
		i64 d = 0;
		while (d == 0) d = rho(m);
		q.push(d), q.push(m/d);
	}
	return fac;
}

int main() {
	i64 m, n;
	cin >> m >> n;
	m--, n--;

	i64 g = gcd(m,n), res = 1 + (m != n);
	for (auto [p,a]: factorize(g)) {
		if (p%4 == 1) res *= 2*a+1;
	}
	cout << res << '\n';
}
