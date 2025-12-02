#include <iostream>
#include <cmath>
#include <numeric>
#include <assert.h>
using namespace std;

int main() {
	int n; cin >> n;

	double max = 0;
	int maxk;
	for(int k = 1; k <= n / 2; ++k) {
		double angle = (2. * 3.1415 * k) / n;
		double cord = 2 * sin(angle / 2);

		long factor = lcm<long, long>(k, n) / k;
		double total = factor * cord;
		if (total > max) {
			maxk = k;
			max = total;
		}
	}

	cout << maxk << endl;
}
