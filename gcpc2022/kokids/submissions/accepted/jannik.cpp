#include <iostream>
#include <vector>

using namespace std;
using ll = long long;

int main() {
	ll n,k; cin >> n >> k;
	string s; cin >> s;

	ll fallen = 0;
	char last = 'R';
	for (ll i = 0; i < n && fallen < k; i++) {
		if (last == s[i])
			fallen++;
		else
			last = s[i];
	}
	cout << (k-fallen) << endl;
	return 0;
}
