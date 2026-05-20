#include <bits/stdc++.h>
using namespace std;

int main() {
	int n; cin >> n;
	
	vector<int> cnt(4*n+1);
	for (int i = 0; i < n; i++) {
		array<int,4> p;
		for (int &x: p) {
			cin >> x;
			cnt[x]++;
		}
		for (int a = 0; a < 4; a++) {
			for (int b = a+1; b < 4; b++) {
				if (p[a] > 0 && p[a] == p[b]) exit(43);
			}
		}
	}
	
	int max_value = 4*n;
	while (cnt[max_value] == 0) max_value--;
	for (int i = 1; i <= max_value; i++) {
		if (cnt[i] != 2) exit(43);
	}
	exit(42);
}
