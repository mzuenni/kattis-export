#include <bits/stdc++.h>
using namespace std;

int main() {
	int n, k; cin >> n >> k;
	vector<int> p(n), d(n), s;
	for (int i = 1; i < n; i++) {
		cin >> p[i];
		p[i]--;
	}
	for (int i = 0; i < n; i++) {
		if (i > 0)
			d[i] = d[p[i]] + 1;
		if (d[i] % k == 0)
			s.push_back(i);
	}
	int m = (int)s.size();
	cout << m << "\n";
	for (int i = 0; i < m; i++)
		cout << s[i] + 1 << " \n"[i + 1 == m];
}