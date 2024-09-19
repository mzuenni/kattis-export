#include <bits/stdc++.h>
using namespace std;

int main() {
	vector<float> dp = {1.0};
	for (int s: {4, 6, 8, 12, 20}) {
		int k; cin >> k;
		while (k--) {
			vector<float> ndp(dp.size() + s);
			for (int x = 0; x < int(dp.size()); x++) {
				for (int y = 1; y <= s; y++) {
					ndp[x+y] += dp[x]/s;
				}
			}
			dp = ndp;
		}
	}
	vector<pair<float,int>> a;
	for (int x = 0; x < int(dp.size()); x++) {
		if (dp[x] > 0) a.emplace_back(dp[x], x);
	}
	sort(begin(a), end(a));
	reverse(begin(a), end(a));
	for (auto [_,x]: a) cout << x << ' ';
}
