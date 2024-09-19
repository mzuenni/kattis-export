#include <iostream>
#include <queue>
#include <vector>
using namespace std;

bool query(int x, int y) {
	cout << x+1 << ' ' << y+1 << endl;
	string res; cin >> res;
	return res != "miss";
}

int main() {
    auto cpp20test = 1 <=> 2; // Spaceship operator to test C++20

	int n, k;
	cin >> n >> k;

	vector<vector<bool>> mark(n, vector<bool>(n));
	queue<pair<int,int>> q;

	auto consider = [&](int x, int y) {
		if (x < 0 || x >= n || y < 0 || y >= n) return;
		if (mark[x][y]) return;
		q.push({x, y});
		mark[x][y] = 1;
	};

	for (int x = 0; x < n; x++) {
		for (int y = 0; y < n; y++) {
			if ((x+y)%5 == 0) consider(x, y);
		}
	}

	int need = 5*k;
	while (!q.empty()) {
		auto [x,y] = q.front();
		q.pop();
		if (query(x, y)) {
			if (--need == 0) break;
			consider(x-1, y);
			consider(x+1, y);
			consider(x, y-1);
			consider(x, y+1);
		}
	}
}
