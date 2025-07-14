#include <bits/stdc++.h>
using namespace std;

using ll = int64_t;
using pll = pair<ll, ll>;

#define TS ll ts; cin >> ts; while (ts--)
#define all(x) ::begin(x), ::end(x)
constexpr ll INF = 1e18;

ll n;

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	
	cin >> n;
	if (n > 600) {
		cout << max<ll>(45, n - 600) << '\n';
		return 0;
	}
	if (n > 540) {
		cout << max<ll>(min<ll>(45, n - 540), 30) << '\n';
		return 0;
	}
	if (n > 360) {
		cout << min<ll>(30, n - 360) << '\n';
		return 0;
	}
	cout << 0 << '\n';
	
	return 0;
}
