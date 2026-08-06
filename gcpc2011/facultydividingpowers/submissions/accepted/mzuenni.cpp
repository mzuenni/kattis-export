#include <bits/stdc++.h>
using namespace std;

#define fora(i, n) for (int i = 0; i < n; ++i)
#define forb(i, n) for (int i = 1; i<= n; ++i)
#define forc(i, n) for (const auto &i : n)
#define mp make_pair
#define eb emplace_back
#define pb push_back
#define sz(x) (int)(x).size()
#define imin(a, b) a = min(a, b)

using ll = unsigned long long;
using ld = long double;
using vi = vector<int>;

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);
	long long t;
	cin >> t;
	for (long long i = 0; i < t; i++) {
		long long n, k;
		cin >> n >> k;
		map<long long, long long> facts;
		long long p = 2;
		while (p * p <= k) {
			while (k % p == 0) {
				facts[p]++;
				k /= p;
			}
			p++;
		}
		if (k > 1) {
			facts[k]++;
		}
		long long res = 0x3FFFFFFFFFFFFFFF;
		for (auto e : facts) {
			unsigned long long p = e.first;
			unsigned long long c = 1;
			long long maxp = 0;
			while ((c * p) / p == c) {
				c *= p;
				maxp += n / c;
			}
			res = min(res, maxp / e.second);
		}
		cout << res << endl;
	}
}
