#include <bits/stdc++.h>
using namespace std;

const int N = 555;
bool vis[2][N][N];

int main() {
	int n, a, b, c, d;
	cin >> n >> a >> b >> c >> d;

	vector<int> dx = {a, a, -a, -a, b, b, -b, -b, c, c, -c, -c, d, d, -d, -d};
	vector<int> dy = {b, -b, b, -b, a, -a, a, -a, d, -d, d, -d, c, -c, c, -c};

	int res = 0;
	for (int sx = 0; sx < n; sx++) {
		for (int sy = 0; sy < n; sy++) {
			queue<tuple<int,int,int>> q;
			memset(vis, 0, sizeof vis);
			vis[0][sx][sy] = 1;
			q.push({0, sx, sy});
			vis[1][sx][sy] = 1;
			q.push({1, sx, sy});

			bool found = false;
			while (!q.empty()) {
				auto [i,x,y] = q.front();
				q.pop();
				if (x == 0 && y == 0) {
					found = true;
					break;
				}

				for (int j = 8*i; j < 8*i+8; j++) {
					int nx = x+dx[j], ny = y+dy[j];
					if (nx < 0 || nx >= n || ny < 0 || ny >= n) continue;
					if (vis[1-i][nx][ny]) continue;
					vis[1-i][nx][ny] = 1;
					q.push({1-i, nx, ny});
				}
			}
			res += found;
		}
	}
	cout << res << '\n';
}
