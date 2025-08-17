#include <bits/stdc++.h>
using namespace std;

int main() {
	int n, m;
	cin >> n >> m;

	set<int> s;
	while (m--) {
		int i, d, c;
		cin >> i >> d >> c;
		s.insert(i);
	}
	
	for (int i = 1; i < n; i++) {
		if (!s.count(i)) exit(43);
	}

	exit(42);
}
