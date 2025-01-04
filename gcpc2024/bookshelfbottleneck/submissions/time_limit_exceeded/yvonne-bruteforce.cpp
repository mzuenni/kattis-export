#include <iostream>
#include <vector>
#include <array>

using namespace std;

int64_t solve(vector<array<int64_t, 3>>& books, int i, int h) {
	if (i == books.size())
		return 0;
	
	int64_t val = 1e18;
	for (int j = 0; j < 3; ++j) {
		for (int k = 0; k < 3; ++k) {
			if (j == k)
				continue;
			if (books[i][k] <= h) {
				int64_t next = solve(books, i+1, h);
				if (next == -1) {
					return -1;
				}
				val = min(val, books[i][j] + next);
			}
		}
	}

	if (val == 1e18)
		return -1;

	return val;
}

int main() {
	int n, h;
	cin >> n >> h;

	vector<array<int64_t, 3>> books(n);
	for(int i = 0; i < n; ++i) {
		cin >> books[i][0] >> books[i][1] >> books[i][2];
	}

	int64_t res = solve(books, 0, h);
	if (res == -1) {
		cout << "impossible" << endl;
		return 0;
	}

	cout << res << endl;
}
