#include <bits/stdc++.h>
using namespace std;

#define all(x) begin(x), end(x)
#define sz(x) (ll)(x).size()

using ll = long long;
using ld = long double;
using bits = bitset<64>;

void solve(ll x) {
	cout << x << endl;
	exit(0);
}

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);
	ll n;
	cin >> n;
	n--;
	bits tmp(n);
	if (tmp.none()) solve(1);
	ll a = tmp._Find_first();
	tmp[a] = false;
	if (tmp.none()) solve(1);
	ll b = tmp._Find_first();
	tmp[b] = false;
	if (tmp.none()) solve((1ll << a)+1);
	cout << "impossible" << endl;
}
