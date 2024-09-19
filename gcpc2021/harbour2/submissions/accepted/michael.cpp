#include <bits/stdc++.h>

using namespace std;

#define all(x) begin(x), end(x)
#define sz(x) (ll)(x).size()

using ll = long long;
using ld = long double;

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);
	ll n, l, r;
	cin >> n >> l >> r;
	n++;
	vector<ll> in(n);
	for (ll i = 0; i < n; i++) cin >> in[i];
	reverse(in.begin()+l, in.end());
	ll mid = -1;
	for (ll i = 0; i < n; i++) if (in[i] == 0) mid = i;
	ll res = 0;
	//answere is jsut the length of the greedy increasing subsequence?
	for (ll i = mid, c = 0; i >= 0; i--) {
		if (in[i] > c) {
			res++;
			c = in[i];
		}
	}
	for (ll i = mid, c = 0; i < n; i++) {
		if (in[i] > c) {
			res++;
			c = in[i];
		}
	}
	cout << res << endl;
}
