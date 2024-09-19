#include <iomanip>
#include <iostream>
using namespace std;

int main() {
	long long n; cin >> n;
	if (n > 100) n = 100;
	double a = 100, b = 0, c = 0, d = 100;
	for (int i = 1; i < n; i++) {
		a = (a+c)/2, b = (b+d)/2;
		swap(a,c), swap(b,d);
	}
	cout << setprecision(10) << a << ' ' << b << '\n';
}
