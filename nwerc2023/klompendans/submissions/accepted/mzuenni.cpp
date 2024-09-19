#include <bits/stdc++.h>
using namespace std;

#define all(x) begin(x), end(x)
#define sz(x) (ll)(x).size()

using ll = long long;
using ld = long double;

bool seen[2][500][500];
ll ac[2];
ll bd[2];
ll n, a, b, c, d;

void dfs(ll w, ll x, ll y) {
	if (x < 0 || x >= n) return;
	if (y < 0 || y >= n) return;
	if (seen[w][y][x]) return;
	seen[w][y][x] = true;
	for (ll dx : {ac[w], -ac[w]}) {
		for (ll dy : {bd[w], -bd[w]}) {
			dfs(w ^ 1, x+dx, y+dy);
			dfs(w ^ 1, x+dy, y+dx);
		}
	}
}

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);

	cin >> n >> ac[0] >> bd[0] >> ac[1] >> bd[1];
	dfs(0, 0, 0);
	dfs(1, 0, 0);
	ll res = 0;
	for (ll i = 0; i < n; i++) {
		for (ll j = 0; j < n; j++) {
			res += seen[0][i][j] || seen[1][i][j];
		}
	}
	cout << res << endl;
}
