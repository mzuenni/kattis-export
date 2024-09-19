#include <bits/stdc++.h>
using namespace std;

int main() {
	int n, m;
	cin >> n >> m;

	vector<vector<int>> a(n);
	for (int i = 0; i < n; i++) {
		for (int j = 0; j <= m && i+j <= n; j++) {
			int x; cin >> x;
			a[i].push_back(x);
		}
	}

	vector<long long> dp(n+1);
	for (int i = n-1; i >= 0; i--) {
		dp[i] = 1e16;
		for (int j = 1; j < a[i].size(); j++) {
			dp[i] = min(dp[i], a[i][0]-a[i][j] + dp[j]);
		}
	}
	cout << dp[0] << '\n';
}
