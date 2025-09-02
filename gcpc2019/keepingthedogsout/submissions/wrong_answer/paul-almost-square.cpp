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

	long long hmax = 0;
	for (long long h = 1; h*h <= area; h++) {
		if (area % h == 0) hmax = h;
	}

	long long w = area/hmax;
	long long sum = 0;
	bool ok = true;
	for (int i = n; i >= 0; i--) {
		sum = 4*sum + a[i];
		if (sum > (hmax >> i) * (w >> i)) ok = false;
	}
	if (ok) cout << hmax << " " << w << endl;
	else cout << "impossible" << endl;
}
