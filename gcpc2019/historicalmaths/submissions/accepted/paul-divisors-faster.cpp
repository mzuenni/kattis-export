#include <bits/stdc++.h>
using namespace std;
using i64 = unsigned long long;
using i128 = __uint128_t;

i64 mul_mod(i64 a, i64 b, i64 m) {
	return i128(a)*b % m;
}

i64 exp_mod(i64 a, i64 n, i64 m) {
	if (m == 1) return 0;
	i64 res = 1;
	for (; n > 0; n /= 2) {
		if (n%2 == 1) res = mul_mod(res,a,m);
		a = mul_mod(a,a,m);
	}
	return res;
}

// Miller-Rabin primality test
bool is_prime(i64 n) {
	if (n < 2) return false;
	if (n%2 == 0) return n == 2;
    i64 s = 0, d = n-1;
    while (d%2 == 0) d /= 2, s++;
    for (i64 a = 2; a < min(n,50ULL); a++) {
        i64 p = exp_mod(a,d,n);
        if (p == 1) continue;
		for (i64 i = 0; i < s-1; i++) {
			if (p == n-1) break;
			p = mul_mod(p,p,n);
		}
		if (p != n-1) return false;
	}
	return true;
}

// Integer factorization using Pollard's rho algorithm
i64 pollard(i64 n) {
	if (n%2 == 0) return 2;
	auto f = [&](i64 x) { return (mul_mod(x,x,n) + 1) % n; };
    for (i64 i = 2; i < n; i++) {
		i64 x = i, y = f(i), g;
		while ((g = __gcd(n+y-x,n)) == 1) x = f(x), y = f(f(y));
		if (g != n) return g;
	}
	return -1;
}

vector<pair<i64,int>> factorize(i64 n) {
	map<i64,int> freq;
	function<void(i64)> rec = [&](i64 n) {
		if (is_prime(n)) {
			freq[n]++;
		} else if (n > 1) {
			i64 x = pollard(n);
			rec(x), rec(n/x);
		}
	};
	rec(n);
	return vector<pair<i64,int>>(begin(freq),end(freq));
}

// Generate a list of all divisors
vector<i64> divisors(i64 n) {
	vector<i64> divs = {1};
	auto facs = factorize(n);
	for (auto pr: facs) {
		vector<i64> new_divs;
		i64 y = 1;
		for (int i = 0; i <= pr.second; i++) {
			for (i64 x: divs) new_divs.push_back(x*y);
			y *= pr.first;
		}
		divs = new_divs;
	}
    return divs;
}

vector<i64> read_poly() {
	int n; cin >> n;
	vector<i64> a(n);
	for (int i = 0; i < n; i++) cin >> a[i];
	reverse(begin(a), end(a));
	return a;
}

void fail() {
	cout << "impossible" << endl;
	exit(0);
}

i64 find_base() {
	vector<i64> a = read_poly();
	vector<i64> b = read_poly();
	vector<i64> c = read_poly();

	
	vector<i128> ab(a.size() + b.size());
	for (int i = 0; i < int(a.size()); i++) {
		for (int j = 0; j < int(b.size()); j++) {
			ab[i+j] += a[i]*b[j];
		}
	}
	
	int n = max(ab.size(), c.size()) + 2;
	ab.resize(n), c.resize(n);
	
	i64 Bmin = 2;
	Bmin = max(Bmin, *max_element(begin(a), end(a)) + 1);
	Bmin = max(Bmin, *max_element(begin(b), end(b)) + 1);
	Bmin = max(Bmin, *max_element(begin(c), end(c)) + 1);
	
	i64 Bmult = 0;
	for (int i = 0; i < n; i++) {
		if (ab[i] != c[i]) {
			if (ab[i] < c[i]) fail();
			Bmult = ab[i]-c[i];
			break;
		}
	}
	if (Bmult == 0) return Bmin;
	
	assert(Bmult < LLONG_MAX);
	
	for (i64 B: divisors(Bmult)) {
		if (B < Bmin) continue;
		
		bool ok = true;
		i128 carry = 0;
		for (int i = 0; i < n; i++) {
			carry += ab[i];
			if (carry % B != c[i]) {
				ok = false;
				break;
			}
			carry /= B;
		}
		if (carry > 0) ok = false;

		if (ok) return B;
	}
	
	fail();
}

int main() {
	cout << find_base() << endl;
}
