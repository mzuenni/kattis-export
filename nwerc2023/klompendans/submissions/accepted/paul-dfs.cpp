#include <bits/stdc++.h>
using namespace std;

const int N = 555;
int n;
vector<int> dx, dy;
bool vis[2][N][N];

void dfs(int i, int x, int y) {
	if (x < 0 || x >= n || y < 0 || y >= n) return;
	if (vis[i][x][y]) return;
	vis[i][x][y] = 1;

	for (int j = 8*i; j < 8*i+8; j++) {
		dfs(1-i, x+dx[j], y+dy[j]);
	}
}

int main() {
	int a, b, c, d;
	cin >> n >> a >> b >> c >> d;

	dx = {a, a, -a, -a, b, b, -b, -b, c, c, -c, -c, d, d, -d, -d};
	dy = {b, -b, b, -b, a, -a, a, -a, d, -d, d, -d, c, -c, c, -c};

	dfs(0, 0, 0);
	dfs(1, 0, 0);

	int res = 0;
	for (int x = 0; x < n; x++) {
		for (int y = 0; y < n; y++) {
			res += max(vis[0][x][y], vis[1][x][y]);
		}
	}
	cout << res << '\n';
}
