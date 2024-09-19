#include <iomanip>
#include <iostream>
using namespace std;

int main() {
	int n; cin >> n;
	double a = 100, b = 0, c = 0, d = 100;
	for (int i = 1; i < n; i++) {
		a = (a+c)/2, b = (b+d)/2;
		swap(a,c), swap(b,d);
	}
	cout << setprecision(10) << a << ' ' << b << '\n';
}
