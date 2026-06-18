#include <bits/stdc++.h>
using namespace std;

int main() {
	int n, k; cin >> n >> k;
	vector<int> p(n), d(n), s;
	for (int i = 1; i < n; i++) {
		cin >> p[i];
		p[i]--;
	}
	s.push_back(0);
	for (int i = n - 1; i > 0; i--) {
		if (d[i] == k - 1)
			s.push_back(i);
		else
			d[p[i]] = max(d[p[i]], d[i] + 1);
	}
	int m = (int)s.size();
	cout << m << "\n";
	for (int i = 0; i < m; i++)
		cout << s[i] + 1 << " \n"[i + 1 == m];
}