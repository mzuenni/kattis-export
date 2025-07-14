#include <vector>
#include <iostream>
#include <algorithm>
#include <random>
using namespace std;

int main() {
	cin.sync_with_stdio(0);

	int n, a, b;
	bool swapped = false;

	cin >> n >> a >> b;

	vector<int> row(n);
	for(int i = 0; i < n; ++i) {
		row[i] = i + 1;
	}

	auto rng = std::default_random_engine {};
	constexpr int MAXI = 100000;
	for (int i = 0; i < MAXI; ++i) {
		shuffle(begin(row), end(row), rng);

		int left = 0, right = 0;
		int li = 0, ri = 0;
		for (int j = 0; j < n; ++j) {
			if (li < row[j]) {
				++left; li = row[j];
			}
		}
		for (int j = n; j-- > 0;) {
			if (ri < row[j]) {
				++right; ri = row[j];
			}
		}
		if (left == b && right == a) {
			swap(left, right);
			reverse(begin(row), end(row));
		}
		if (left == a && right == b) {
			cout << "yes" << endl;
			for(int i = 0; i < row.size(); ++i) {
				cout << row[i] << ' ';
			}
			cout << endl;
			return 0;
		}
	}

	cout << "no" << endl;
}
