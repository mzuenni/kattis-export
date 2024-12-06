#include <iomanip>
#include <iostream>
#include <vector>
using namespace std;

using T = double;

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

	auto a = [&](int i, int j) -> double {
		auto dx = x[i] - x[j];
		auto dy = y[i] - y[j];
		return dx * y[i] - dy * x[i];
	};

	T area = 0;
	for(int i = 0; i < n; ++i) {
		area += a(i, i + 1);
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
