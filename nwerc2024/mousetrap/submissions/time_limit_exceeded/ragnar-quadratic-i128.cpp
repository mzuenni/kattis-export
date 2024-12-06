#include <iomanip>
#include <iostream>
#include <vector>
using namespace std;

using i128 = __int128;

int main() {
	int n;
	cin >> n;
	vector<i128> x(2 * n), y(2 * n);
	for(int i = 0; i < n; ++i) {
		long long _x, _y;
		cin >> _x >> _y;
		x[i + n] = x[i] = _x;
		y[i + n] = y[i] = _y;
	}

	i128 area = 0;
	for(int i = 0; i < n; ++i) {
		area += x[i] * y[i + 1] - x[i + 1] * y[i];
	}
	i128 ans = 0;
	for(int i = 0; i < n; ++i) {
		for(int j = i + 1; j < i + n; ++j) {
			ans += (x[j] * y[i] - x[i] * y[j]) * (j - i - 1);
		}
	}
	cout << fixed << setprecision(20) << (double)ans / (double)area << endl;
}
