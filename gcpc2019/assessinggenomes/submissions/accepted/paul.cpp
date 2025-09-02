#include <bits/stdc++.h>
using namespace std;

int period(string s) {
	int n = s.size();
	for (int i = 1; i < n; i++) {
		if (n%i == 0 && s.substr(i) == s.substr(0,n-i)) return i;
	}
	return n;
}

int score[2][100];

int main() {
	int n; cin >> n;
	for (int i = 0; i < 2; i++) {
		for (int j = 0; j < n; j++) {
			string s; cin >> s;
			score[i][j] = period(s);
		}
		sort(score[i],score[i]+n);
	}

	int res = 0;
	for (int i = 0; i < n; i++) {
		int cur = score[0][i] - score[1][i];
		res += cur*cur;
	}
	cout << res << endl;
}
