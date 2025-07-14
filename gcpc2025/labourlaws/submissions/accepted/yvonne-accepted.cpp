#include <iostream>

using namespace std;

int main() {
	int t;
	cin >> t;

	if (t <= 6 * 60) {
		// less than 6 hours
		cout << 0 << endl;
	} else if (t <= 9 * 60 + 30) {
		cout << min(30, t - 6 * 60) << endl;
	} else if (t <= 10 * 60 + 45) {
		cout << min(45, t - 9 * 60) << endl;
	} else {
		cout << (t - 10 * 60) << endl;
	}
}
