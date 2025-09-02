#include <bits/stdc++.h>
using namespace std;

int main() {
	int n, m; cin >> n >> m;

	vector<int> dp(m,0);
	for (int i = 0; i < n; i++) {
		int x; cin >> x;
		if (i < m) continue;
		dp[i%m] = max(dp[(i-1)%m], x+dp[i%m]);
	}
	cout << dp[(n-1)%m] << endl;
}
