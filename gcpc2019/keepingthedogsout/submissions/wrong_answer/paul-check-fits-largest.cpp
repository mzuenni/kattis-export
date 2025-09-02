#include <bits/stdc++.h>
using namespace std;

int main() {
	int n; cin >> n;
	long long area = 0;

	int j = 0;
	for (int i = 0; i <= n; i++) {
		long long x; cin >> x;
		area += x << (2*i);
		if (x > 0) j = i;
	}

	for (long long h = 1 << j; h*h <= area; h++) {
		if (area%h == 0) {
			cout << h << " " << area/h << endl;
			return 0;
		}
	}
	cout << "impossible" << endl;
}
