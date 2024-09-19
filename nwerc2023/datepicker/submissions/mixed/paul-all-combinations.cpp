// @EXPECTED_RESULTS@: ACCEPTED, TIME_LIMIT_EXCEEDED
// Loops over subsets of both rows and columns and sums using the popcount operation.
// This is rather silly, so it doesn't matter if it's AC or TLE.

// This compiler option supposedly speeds up the popcount operation on some
// architectures, but leads to a crash on the CI. I don't care enough to investigate.
// #pragma GCC target("popcnt")
#include <bits/stdc++.h>
using namespace std;

void next_mask(int &x) {
	int c = x & -x, r = x + c;
	x = r | (((r^x) >> 2) / c);
}

int main() {
	vector<string> a(7);
	for (string &s: a) cin >> s;

	vector<int> v(7);
	for (int i = 0; i < 7; i++) {
		for (int j = 0; j < 24; j++) {
			v[i] |= int(a[i][j] == '.') << j;
		}
	}

	int d, h;
	cin >> d >> h;

	int res = 0;
	for (int x = (1 << d) - 1; x < (1 << 7); next_mask(x)) {
		vector<int> w;
		for (int i = 0; i < 7; i++) {
			if (x & (1 << i)) w.push_back(v[i]);
		}
		for (int y = (1 << h) - 1; y < (1 << 24); next_mask(y)) {
			int cur = 0;
			for (int z: w) cur += __builtin_popcount(y&z);
			res = max(res, cur);
		}
	}
	cout << fixed << setprecision(20) << res/double(d*h) << '\n';
}
