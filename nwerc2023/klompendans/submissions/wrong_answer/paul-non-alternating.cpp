#include <bits/stdc++.h>
using namespace std;

const int N = 555;
bool vis[N][N];

int main() {
	int n, a, b, c, d;
	cin >> n >> a >> b >> c >> d;

	vector<int> dx = {a, a, -a, -a, b, b, -b, -b, c, c, -c, -c, d, d, -d, -d};
	vector<int> dy = {b, -b, b, -b, a, -a, a, -a, d, -d, d, -d, c, -c, c, -c};

	queue<pair<int,int>> q;
	vis[0][0] = 1;
	q.push({0, 0});

	while (!q.empty()) {
		auto [x,y] = q.front();
		q.pop();

		for (int j = 0; j < 16; j++) {
			int nx = x+dx[j], ny = y+dy[j];
			if (nx < 0 || nx >= n || ny < 0 || ny >= n) continue;
			if (vis[nx][ny]) continue;
			vis[nx][ny] = 1;
			q.push({nx, ny});
		}
	}

	int res = 0;
	for (int x = 0; x < n; x++) {
		for (int y = 0; y < n; y++) {
			res += vis[x][y];
		}
	}
	cout << res << '\n';
}
