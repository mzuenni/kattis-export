#include <iomanip>
#include <iostream>
#include <vector>
using namespace std;
int main() {
	int n;
	cin >> n;
	vector<double> x(2 * n), y(2 * n);
	for(int i = 0; i < n; ++i) {
		cin >> x[i] >> y[i];
		x[i + n] = x[i];
		y[i + n] = y[i];
	}

	auto a = [&](int i, int j) -> double {
		auto dx = x[i] - x[j];
		auto dy = y[i] - y[j];
		return dx * y[i] - dy * x[i];
	};

	double area = 0;
	for(int i = 0; i < n; ++i) {
		area += a(i, i + 1);
	}
	double ans = 0;
	for(int i = 0; i < n; ++i) {
		for(int j = i + 1; j < i + n; ++j) {
			ans += a(j, i) * (j - i - 1);
		}
	}
	cout << fixed << setprecision(20) << ans / area << endl;
}
