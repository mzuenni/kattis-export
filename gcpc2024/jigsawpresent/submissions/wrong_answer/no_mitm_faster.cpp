#include <bits/stdc++.h>
using namespace std;
const int C = 4'100;
const int N = 22;

bitset<N * C + 1> vis[(2 * C + 1) * N];
pair<int, int> a[N];
int ord[N];

void print(int x, int y) {
	if (x == y) return;
	cout << "no\n";
	for (int msk: {x, y}) {
		cout << __builtin_popcount(msk) << " ";
		for (int i = 0; i < N; i++)
			if (msk >> i & 1)
				cout << i + 1 << " ";
		cout << "\n";
	}
	exit(0);
}

void dfs2(int x, int y, int m, int mskL, int mskR) {
	if (!x && !y) print(mskL, mskR);
	if (m >= 0) {
		dfs2(x, y, m - 1, mskL, mskR);
		dfs2(x - a[ord[m]].first, y - a[ord[m]].second, m - 1, mskL | (1 << ord[m]), mskR);
	}
}

void dfs(int x, int y, int m, int mx, int msk) {
	if (m < 0) return;
	dfs(x, y, m - 1, mx, msk);
	x += a[ord[m]].first;
	y += a[ord[m]].second;
	msk |= 1 << ord[m];
	if (0 < x + N * C && x + N * C < (2 * C + 1) * N && y <= N * C) {
		if (vis[x + N * C][y])
			dfs2(x, y, mx - 1, 0, msk);
		vis[x + N * C][y] = 1;
	}
	dfs(x, y, m - 1, mx, msk);
}

int main() {
	ios_base::sync_with_stdio(false); cin.tie(0);
	int n; cin >> n;
	n = min(n, N);
	vis[0 + N * C][0] = 0;
	for (int i = 0; i < n; i++)
		cin >> a[i].second >> a[i].first, ord[i] = i;
	vis[0 + N * C][0] = 1;
	mt19937 rng(42);
	shuffle(ord, ord + n, rng);
	for (int i = 0; i < n; i++)
		dfs(a[ord[i]].first, a[ord[i]].second, i - 1, i, 1 << ord[i]);
	cout << "yes\n";
}