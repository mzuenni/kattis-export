#include <bits/stdc++.h>
using namespace std;

int main() {
	int m, n;
	cin >> m >> n;

	vector<int> dp(n+1);
	while (m--) {
		string s; cin >> s;
		vector<int> ndp(n+1);
		
		for (int i = n-1; i >= 0; i--) {
			ndp[i] = max(ndp[i+1], dp[i]);
			if (s[i] == 'C') ndp[i] = max(ndp[i], 1 + dp[i+1]);
		}

		dp = ndp;
	}

	cout << dp[0] << endl;
}
