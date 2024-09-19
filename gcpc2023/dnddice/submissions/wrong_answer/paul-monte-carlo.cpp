#include <bits/stdc++.h>
using namespace std;

int main() {
	srand(123);

	array<int,5> a, b = {4, 6, 8, 12, 20};
	for (int &x: a) cin >> x;

	vector<int> count(1000);
	for (int i = 0; i < 1e6; i++) {
		int s = 0;
		for (int i = 0; i < 5; i++) {
			for (int j = 0; j < a[i]; j++) {
				s += 1 + rand()%b[i];
			}
		}
		count[s]++;
	}

	vector<int> v;
	for (int s = 0; s < 1000; s++) {
		if (count[s] > 0) v.push_back(s);
	}
	sort(begin(v), end(v), [&](int s, int t) { return count[s] > count[t]; });
	for (int x: v) cout << x << ' ';
	cout << '\n';
}
