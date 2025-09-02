#include <bits/stdc++.h>
using namespace std;

int main() {
	int n; cin >> n;
	vector<long long> a(n+1);
	long long area = 0;
	for (int i = 0; i <= n; i++) {
		cin >> a[i];
		area += a[i] << (2*i);
	}

	bool found = false;
	for (long long h = 1; h*h <= area; h++) {
		long long w = area/h;
		long long sum = 0;
		bool ok = true;
		for (int i = n; i >= 0; i--) {
			sum = 4*sum + a[i];
			if (sum > (h >> i) * (w >> i)) ok = false;
		}
		if (ok) {
			cout << h << " " << w << endl;
			found = true;
		}
	}
	if (!found) cout << "impossible" << endl;
}
