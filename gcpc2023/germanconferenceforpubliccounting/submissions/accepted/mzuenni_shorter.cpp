#include <bits/stdc++.h>
using namespace std;

#define all(x) begin(x), end(x)
#define sz(x) (ll)(x).size()

using ll = long long;
using ld = long double;

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);

	string s;
	cin >> s;
	ll res = 10 * sz(s) - (sz(s) > 1);
	for (char i = '1'; i <= '9'; i++) {
		for (char c : s) {
			if (c > i) break;
			if (c < i) {
				res--;
				break;
			}
		}
	}
	cout << res << endl;
}
