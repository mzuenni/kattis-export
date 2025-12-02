#include <iostream>
#include <numeric>
using namespace std;

int main() {
	int n;
	cin >> n;
	for (int k = n/2; k; k--) if (gcd(n, k) == 1) {
		cout << k << endl;
		return 0;
	}
}
