#include <iostream>
#include <set>

using namespace std;

using ll = long long;

int main() {
    ios::sync_with_stdio(0), cin.tie(0);
	
	ll n,q;
	cin >> n >> q;
	set<ll> closed;

	while (q-- > 0) {
		char c; ll a;
		cin >> c >> a;
		if (c == '-') {
			closed.emplace(a);
		} else if (c == '+') {
			closed.erase(a);
		} else {
			ll b; cin >> b;
			if (a > b) swap(a,b);
			auto it_a = closed.lower_bound(a);
			bool possible = (it_a == closed.end() || *it_a > b);
			if (closed.upper_bound(a) == closed.begin() && closed.lower_bound(b) == closed.end())
				possible = true;
			cout << ("impossible\n" + 2*possible);
		}
	}

	return 0;
}
