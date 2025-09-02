#include <bits/stdc++.h>
using namespace std;

int period(string s) {
	int n = s.size();
	for (int i = 1; i < n; i++) {
		if (n%i == 0 && s.substr(i) == s.substr(0,n-i)) return i;
	}
	return n;
}

bool mark[2][100];
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
	for (int k = 0; k < n; k++) {
		int best = INT_MAX, bi, bj;
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < n; j++) {
				int cur = score[0][i] - score[1][j];
				cur *= cur;
				if (!mark[0][i] && !mark[1][j] && cur < best) {
					best = cur, bi = i, bj = j;
				}
			}
		}
		mark[0][bi] = mark[1][bj] = true;
		res += best;
	}
	cout << res << endl;
}
