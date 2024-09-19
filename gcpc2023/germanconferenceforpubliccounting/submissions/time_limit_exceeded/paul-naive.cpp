#include <bits/stdc++.h>
using namespace std;

int main() {
	int n; cin >> n;
	vector<int> a(10);
	for (; n >= 0; n--) {
		vector<int> b(10);
		if (n == 0) b[0]++;
		for (int x = n; x > 0; x /= 10) b[x%10]++;
		for (int d = 0; d < 10; d++) a[d] = max(a[d], b[d]);
	}
	cout << accumulate(begin(a), end(a), 0) << '\n';
}
