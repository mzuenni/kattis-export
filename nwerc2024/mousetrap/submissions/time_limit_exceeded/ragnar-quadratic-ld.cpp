#include <iomanip>
#include <iostream>
#include <vector>
using namespace std;
int main() {
	int n;
	cin >> n;
	vector<long double> x(2 * n), y(2 * n);
	for(int i = 0; i < n; ++i) {
		cin >> x[i] >> y[i];
		x[i + n] = x[i];
		y[i + n] = y[i];
	}
	long double area = 0;
	for(int i = 0; i < n; ++i) {
		area += x[i] * y[i + 1] - x[i + 1] * y[i];
	}
	long double ans = 0;
	for(int i = 0; i < n; ++i) {
		for(int j = i + 1; j < i + n; ++j) {
			ans += (x[j] * y[i] - x[i] * y[j]) * (j - i - 1);
		}
	}
	cout << fixed << setprecision(20) << ans / area << endl;
}
