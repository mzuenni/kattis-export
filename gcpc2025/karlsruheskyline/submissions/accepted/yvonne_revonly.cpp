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

	if (a + b > n) {
		cout << "no" << endl;
		return 0;
	}

	vector<int> row(n);
	for(int i = 0; i < n; ++i) {
		row[i] = i + 1;
	}

	reverse(begin(row), end(row));
	reverse(begin(row), begin(row) + a);

	reverse(begin(row) + a, end(row));
	reverse(end(row) - b, end(row));

	if (swapped) {
		reverse(begin(row), end(row));
	}

	cout << "yes" << endl;
	for(int i = 0; i < row.size(); ++i) {
		cout << row[i] << ' ';
	}
	cout << endl;
}
