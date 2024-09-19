#include <algorithm>
#include <iostream>
#include <queue>
#include <random>
#include <vector>
using namespace std;

bool query(int x, int y) {
	cout << x+1 << ' ' << y+1 << endl;
	string res; cin >> res;
	return res != "miss";
}

int main() {
	int n, k;
	cin >> n >> k;

	vector<vector<bool>> mark(n, vector<bool>(n));
	queue<pair<int,int>> q;
	vector<pair<int,int>> cells;

	auto consider = [&](int x, int y) {
		if (x < 0 || x >= n || y < 0 || y >= n) return;
		if (mark[x][y]) return;
		q.push({x, y});
		mark[x][y] = 1;
	};

	for (int x = 0; x < n; x++) {
		for (int y = 0; y < n; y++) {
			cells.emplace_back(x, y);
		}
	}
	mt19937_64 gen(123);
	shuffle(begin(cells), end(cells), gen);

	int need = 5*k, pos = 0;
	while (need > 0) {
		while (q.empty()) {
			auto [x, y] = cells[pos++];
			consider(x, y);
		}
		auto [x, y] = q.front();
		q.pop();
		if (query(x, y)) {
			consider(x-1, y);
			consider(x+1, y);
			consider(x, y-1);
			consider(x, y+1);
			need--;
		}
	}
}
