#include <iomanip>
#include <iostream>
#include <vector>
using namespace std;

using T = __int128;

int main() {
	int n;
	cin >> n;
	vector<T> x(2 * n), y(2 * n);

	T sum_x = 0, sum_y = 0;

	for(int i = 0; i < n; ++i) {
		long long _x, _y;
		cin >> _x >> _y;
		x[i + n] = x[i] = _x;
		y[i + n] = y[i] = _y;
		sum_x += _x;
		sum_y += _y;
	}

	T area = 0;
	for(int i = 0; i < n; ++i) {
		area += x[i] * y[i + 1] - x[i + 1] * y[i];
	}

	T Sx = 0, Sy = 0;
	for(int i = 1; i < n; ++i) {
		Sx += (i - 1) * x[i];
		Sy += (i - 1) * y[i];
	}

	T ans = 0;
	for(int i = 0; i < n; ++i) {
		ans -= x[i] * Sy;
		ans += y[i] * Sx;

		Sx += (n - 1) * x[i] + x[i + 1] - sum_x;
		Sy += (n - 1) * y[i] + y[i + 1] - sum_y;
	}
	cout << fixed << setprecision(20) << (double)ans / (double)area << endl;
}
