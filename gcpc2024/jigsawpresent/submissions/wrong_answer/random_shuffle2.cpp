#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int C = 4'100;
const int N = 63;

map<int, ll> vis[(2 * C + 1) * N];
pair<int, int> a[N];

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
	for (int i = 0; i < n; i++)
		cin >> a[i].second >> a[i].first;
	mt19937 rng(42);
	vector<int> ind(n);
	iota(ind.begin(), ind.end(), 0);
	auto t = chrono::steady_clock::now();

	auto cur_time = [&]() {
		auto t2 = chrono::steady_clock::now();
		return chrono::duration_cast<chrono::milliseconds>(t2 - t).count();
	};
	
	vis[0 + N * C][0] = 0;
	while (cur_time() < 2000) {
		shuffle(ind.begin(), ind.end(), rng);
		int x = 0, y = 0;
		ll msk = 0;
		for (int i: ind) {
			msk |= 1ll << i;
			x += a[i].first;
			y += a[i].second;
			if (vis[x + N * C].count(y) && vis[x + N * C][y] != msk)
				print(msk, vis[x + N * C][y]);
			vis[x + N * C][y] = msk;
		}
	}
	cout << "yes\n";
}