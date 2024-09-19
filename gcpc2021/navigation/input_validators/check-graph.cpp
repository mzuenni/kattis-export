#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;

int main() {
	int n, m, k;
	cin >> n >> m >> k;

	int sum = 0;
	while (m--) {
		int a, b, len;
		cin >> a >> b >> len >> k;

		sum += k;

		// self-loops allowed!
		//if (a == b) exit(43);

		vector<int> c(k);
		for (int &x: c) cin >> x;

		// outgoing colors must be distinct
		sort(begin(c), end(c));
		if (unique(begin(c), end(c)) != end(c)) exit(43);
	}

	// total number of visible colors must be bounded
	if (sum > 500'000) exit(43);

	exit(42);
}
