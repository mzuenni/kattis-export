#include <iostream>
using namespace std;

bool is_prime(int n) {
	if (n < 2) return false;
	for (int k = 2; k*k <= n; k++) {
		if (n%k == 0) return false;
	}
	return true;
}

int main() {
	int n, m, p;
	cin >> n >> m >> p;
	
	exit(is_prime(p) ? 42 : 43);
}
