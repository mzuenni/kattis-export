#include <bits/stdc++.h>
using namespace std;

const int N = 555;
int n;
vector<int> dx, dy;
bool vis[2][N][N];

bool dfs(int i, int x, int y) {
	if (x == 0 && y == 0) return true;
	if (x < 0 || x >= n || y < 0 || y >= n) return false;
	if (vis[i][x][y]) return false;
	vis[i][x][y] = 1;

	for (int j = 8*i; j < 8*i+8; j++) {
		if (dfs(1-i, x+dx[j], y+dy[j])) return true;
	}
	return false;
}

int main() {
	int a, b, c, d;
	cin >> n >> a >> b >> c >> d;

	dx = {a, a, -a, -a, b, b, -b, -b, c, c, -c, -c, d, d, -d, -d};
	dy = {b, -b, b, -b, a, -a, a, -a, d, -d, d, -d, c, -c, c, -c};

	int res = 0;
	for (int x = 0; x < n; x++) {
		for (int y = 0; y < n; y++) {
			memset(vis, 0, sizeof vis);
			res += dfs(0, x, y) || dfs(1, x, y);
		}
	}
	cout << res << '\n';
}
