#include <iostream>
#include <vector>

using namespace std;
using ll = long long;

int main() {
	ll n,k; cin >> n >> k;
	string s; cin >> s;
	ll num = 0; // number of known steps
	ll fallen = 0;
	for (ll i = 0; i < k; i++) { // just simulate each player
		char last = 'R';
		for (ll p = 0; p < n; p++) {
			if (p < num) {
				// ok
				last = s[p];
			} else {
				num++;
				if (s[p] != last) { // ok
					last = s[p];
				} else { // fall
					fallen++;
					break;
				}
			}
		}
	}
	cout << (k-fallen) << endl;
	return 0;
}
