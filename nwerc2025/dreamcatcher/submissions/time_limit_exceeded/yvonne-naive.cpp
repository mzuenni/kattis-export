#include <iostream>
#include <cmath>
#include <numeric>
using namespace std;

int main() {
	int n; cin >> n;

	double max = 0;
	int maxk = 1;
	for(int k = 1; k <= n / 2; ++k) {
		double angle = (2. * 3.1415 * k) / n;
		double cord = 2 * sin(angle / 2);

		double total = cord;
		int i = k + 1;
		while (i != 1) {
			total += cord;
			i += k;
			i %= n;
		}
		if (total > max) {
			maxk = k;
			max = total;
		}
	}

	cout << maxk << endl;
}
