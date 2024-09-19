// @EXPECTED_RESULTS@: RUN_TIME_ERROR, TIME_LIMIT_EXCEEDED
// Uses too much memory and too much time
#include <bits/stdc++.h>
using namespace std;

const int N = 555;

bool vis[2][N][N];

int main() {
	int n, a, b, c, d;
	cin >> n >> a >> b >> c >> d;

	vector<int> dx = {a, a, -a, -a, b, b, -b, -b, c, c, -c, -c, d, d, -d, -d};
	vector<int> dy = {b, -b, b, -b, a, -a, a, -a, d, -d, d, -d, c, -c, c, -c};

	queue<tuple<int,int,int>> q;
	vis[0][0][0] = 1;
	q.push({0, 0, 0});
	vis[1][0][0] = 1;
	q.push({1, 0, 0});

	while (!q.empty()) {
		auto [i,x,y] = q.front();
		q.pop();

		for (int j = 8*i; j < 8*i+8; j++) {
			int nx = x+dx[j], ny = y+dy[j];
			if (nx < 0 || nx >= n || ny < 0 || ny >= n) continue;
			vis[1-i][nx][ny] = 1;
			q.push({1-i, nx, ny});
		}
	}

	int res = 0;
	for (int x = 0; x < n; x++) {
		for (int y = 0; y < n; y++) {
			res += max(vis[0][x][y], vis[1][x][y]);
		}
	}
	cout << res << '\n';
}
