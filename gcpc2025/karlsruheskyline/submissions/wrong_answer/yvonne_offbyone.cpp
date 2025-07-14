#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;

int main() {
	int n, a, b;
	bool swapped = false;

	cin >> n >> a >> b;
	if (b == 1) {
		swap(a, b);
		swapped = true;
	}
	if (b == 1) {
		cout << "no" << endl;
		return 0;
	}
	--b;

	// off by one error here
	if (a + b >= n) {
		cout << "no" << endl;
		return 0;
	}

	vector<int> row(n);

	int next = n;

	row[a - 1] = next--;
	row[n - b] = next--;

	for(int i = a - 1; i-- > 0;) {
		row[i] = next--;
	}
	for(int i = b - 1; i-- > 0;) {
		row[n - 1 - i] = next--;
	}

	for(int i = a; i < n - b; ++i) {
		row[i] = next--;
	}

	if (swapped) {
		reverse(begin(row), end(row));
	}

	cout << "yes" << endl;
	for(int i = 0; i < row.size(); ++i) {
		cout << row[i] << ' ';
	}
	cout << endl;
}
