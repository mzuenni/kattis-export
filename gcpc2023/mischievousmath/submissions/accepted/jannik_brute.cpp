#include <iostream>
#include <numeric>
#include <vector>
#include <algorithm>

using namespace std;

using ll = long long;

struct frac {
    ll n, d;
    explicit frac(ll _n, ll _d = 1): n(_n), d(_d) {
        const ll g = gcd(n, d);
        n /= g, d /= g;
        if (d < 0) n = -n, d = -d;
    }
    frac operator+(const frac &rhs) const { return frac(n*rhs.d + d*rhs.n, d*rhs.d); }
    frac operator-(const frac &rhs) const { return frac(n*rhs.d - d*rhs.n, d*rhs.d); }
    frac operator*(const frac &rhs) const { return frac(n*rhs.n, d*rhs.d); }
    frac operator/(const frac &rhs) const { return frac(n*rhs.d, d*rhs.n); }
};


typedef frac(frac::*expop)(const frac&) const;
expop ops[4] = {&frac::operator+,&frac::operator/,&frac::operator-,&frac::operator*};

int main() {
	ll d; cin >> d;
	vector<ll> X(3);
	for (X[0] = 1; X[0] <= 100; X[0]++) if (X[0] != d) {
		for (X[1] = X[0]+1; X[1] <= 100; X[1]++) if (X[1] != d) {
			for (X[2] = X[1]+1; X[2] <= 100; X[2]++) if (X[2] != d)
			{
				bool ok = true;
				do {
					const frac a(X[0]);
					const frac b(X[1]);
					const frac c(X[2]);

					for (ll op = 0; op < 16; op++) {
						const frac ab = (a.*ops[op%4])(b);
						frac l = (a.*ops[op%4])((b.*ops[op/4])(c));
						frac r = (ab.*ops[op/4])(c);
						if (l.d == 1 and l.n == d) { ok = false; break; }
						if (r.d == 1 and r.n == d) { ok = false; break; }
						if (ab.d == 1 and ab.n == d) { ok = false; break; }
					}
				} while (next_permutation(X.begin(), X.end()));

				if (ok) {
					cout << X[0] << ' ' << X[1] << ' ' << X[2] << endl;
					return 0;
				}
			}
		}
	}
	return 1;
}
