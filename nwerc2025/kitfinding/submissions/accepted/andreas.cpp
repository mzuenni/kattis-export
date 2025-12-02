#include <iostream>
using namespace std;

int main() {
	int h, w, k, i, t;
	cin >> h >> w >> k >> i >> t;
	cout << "KIT";
	k--; i--; t--;
	for (int all = k+i+t, col = 3; all > 0; all--, col++) {
		if (col == w) {
			cout << '\n';
			col = 0;
		}
		if (t) {
			cout << "T";
			t--;
		} else if (k) {
			cout << "K";
			k--;
		} else {
			cout << "I";
			i--;
		}
	}
}