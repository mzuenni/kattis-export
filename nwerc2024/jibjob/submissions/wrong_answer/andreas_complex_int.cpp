#include <bits/stdc++.h>
#include <vector>
#include <complex>
using namespace std;

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);

	int n;
	cin >> n;
	vector<complex<int>> p(n);
	vector<int> h(n);
	for (int i = 0; i < n; i++) {
		int x, y;
		cin >> x >> y >> h[i];
		p[i] = complex<int>(x, y);
	}
	for (int i = 0; i < n; i++) {
		int res = h[i];
		for (int j = 0; j < n; j++) if (h[i] < h[j]) {
			res = min(res, abs(p[i] - p[j]));
		}
		cout << res << '\n';
	}

	return 0;
}
