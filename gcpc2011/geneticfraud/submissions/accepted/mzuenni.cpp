#include <bits/stdc++.h>
using namespace std;

#define fora(i, n) for (int i = 0; i < n; ++i)
#define forb(i, n) for (int i = 1; i<= n; ++i)
#define forc(i, n) for (const auto &i : n)
#define mp make_pair
#define eb emplace_back
#define pb push_back
#define sz(x) (int)(x).size()

using ll = long long;
using ld = long double;
using vi = vector<int>;

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);
	long long t;
	cin >> t;
	for (long long i = 0; i < t; i++) {
		long long n;
		cin >> n;
		string a, b;
		cin >> a >> b;
		long long maxRes = 0;
		for (long long i = -(n + 1) / 2; i <= (n + 1) / 2; i++) {
			long long last = max(i, 0ll);
			for (long long j = max(i, 0ll); j < min(n, i + n); j++) {
				if (abs(b[j] - a[j-i]) > 1) {
					maxRes = max(maxRes, abs(last - j));
					last = j + 1;
				}
			}
			maxRes = max(maxRes, abs(last - min(n, i + n)));
		}
		if (maxRes >= (n + 1) / 2) {
			cout << "POSITIVE" << endl;
		} else {
			cout << "NEGATIVE" << endl;
		}
	}
	
}
