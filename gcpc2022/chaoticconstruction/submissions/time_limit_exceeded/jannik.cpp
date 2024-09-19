#include <iostream>
#include <vector>

using namespace std;

using ll = long long;

int main() {
    ios::sync_with_stdio(0), cin.tie(0);
	
	ll n,q;
	cin >> n >> q;
	vector<ll> closed;
	vector<bool> opened(n, true);

	while (q-- > 0) {
		char c; ll a;
		cin >> c >> a;
		if (c == '-') {
			closed.emplace_back(a);
			opened[a] = false;
		} else if (c == '+') {
			opened[a] = true;
		} else {
			ll b; cin >> b;
			if (a > b) swap(a,b);
			ll possible = 0x1 | 0x2;
			for (ll i = 0; i < closed.size(); i++) {
				const ll x = closed[i];
				if (opened[x]) {
					closed[i] = closed.back(); closed.pop_back();
					i--;
					continue;
				}

				if (a == x || b == x) {
					possible = 0;
					break;
				} else if (a < x && x < b) {
					possible &= ~1;
					if (possible == 0) break;
				} else {
					possible &= ~2;
					if (possible == 0) break;
				}
			}
			cout << ("impossible\n" + 2*!!possible);
		}
	}

	return 0;
}
