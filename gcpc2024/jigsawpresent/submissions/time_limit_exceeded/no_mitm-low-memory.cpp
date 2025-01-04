#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int C = 4'100;
const int N = 28;

pair<int, int> a[N];
int ord[N];

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

void dfs(int x, int y, int m, ll mskL, ll mskR) {
	if (!x && !y)
		print(mskL, mskR);
	if (m < 0) return;
	dfs(x, y, m - 1, mskL, mskR);
	dfs(x + a[ord[m]].first, y + a[ord[m]].second, m - 1, mskL | (1ll << ord[m]), mskR);
	dfs(x - a[ord[m]].first, y - a[ord[m]].second, m - 1, mskL, mskR | (1ll << ord[m]));
}

int main() {
	ios_base::sync_with_stdio(false); cin.tie(0);
	int n; cin >> n;
	n = min(n, 2 * N);
	for (int i = 0; i < n; i++)
		cin >> a[i].second >> a[i].first, ord[i] = i;
	mt19937 rng(42);
	shuffle(ord, ord + n, rng);
	for (int i = 0; i < n; i++)
		dfs(a[ord[i]].first, a[ord[i]].second, i - 1, 1ll << ord[i], 0);
	cout << "yes\n";
}