#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int C = 5'000;
const int N = 30;

void print(ll x, ll y) {
	cout << "no\n";
	for (ll msk: {x, y}) {
		cout << __builtin_popcountll(msk) << " ";
		for (ll i = 0; i < N; i++)
			if (msk >> i & 1)
				cout << i + 1 << " ";
		cout << "\n";
	}
	exit(0);
}

int main() {
	ios_base::sync_with_stdio(false); cin.tie(0);
	int n; cin >> n;
	n = min(n, N);
	print((1ll << n) - 1, (1ll << n) - 1);
}