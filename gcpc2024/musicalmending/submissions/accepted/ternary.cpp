#include <iostream>
#include <vector>
#include <cassert>

using namespace std;

int main() {
	int n; cin >> n;

	vector<int> notes(n);
	for(int i = 0; i < n; ++i) {
		cin >> notes[i];
	}

	auto tune = [&](int ref) {
		long res = 0;
		for (int i = 0; i < n; ++i) {
			res += abs(ref - notes[i] + i);
		}

		// minimize function
		return -res;
	};

	int l = -300000;
	int r = 200000;

	while (r - l > 1) {
		int mid = (r + l) / 2;

		if (tune(mid) < tune(mid + 1)) {
			l = mid;
		} else {
			r = mid;
		}
	}

	cout << -tune(r) << endl;
}
