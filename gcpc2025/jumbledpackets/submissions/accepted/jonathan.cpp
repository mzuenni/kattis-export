#include <bits/stdc++.h>
using namespace std;

using ll = int64_t;
using pll = pair<ll, ll>;

#define TS ll ts; cin >> ts; while (ts--)
#define all(x) ::begin(x), ::end(x)
constexpr ll INF = 1e18;

string s;

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	
	string t;
	cin >> t;

	if (t == "Encode") {
		if (count(all(s), '0') == 0 || count(all(s), '1') == 0) {
			cout << s << '\n';
		}
		else {
			ll i = 0;
			while (s[i] == s[0]) {
				cout << '2';
				++i;
			}
			cout << s.substr(i) << '\n';
		}
	}
	else {
		ll t = s.find('2');
		if (t == string::npos) {
			cout << s << '\n';
		}
		else {
			for (ll i = 0; i < s.size(); ++i) {
				cout << s[(i + t) % s.size()] << '\n';
			}
		}
	}
	
	return 0;
}
