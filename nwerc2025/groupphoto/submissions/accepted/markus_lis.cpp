#include <bits/stdc++.h>

int main() {
	std::cin.tie(0)->sync_with_stdio(false);
	int n; std::cin >> n;
	std::vector<std::pair<int, int>> v;
	for (int i = 0; i < n; ++i) {
		int a; std::cin >> a;
		if (a - i - 1 >= 0) v.push_back({ 2 * i + 1, 2 * (a - i - 1) });
		if (a - n + i >= 0) v.push_back({ 2 * (a - n + i), 2 * (n - i) - 1 });
	}
	std::sort(v.begin(), v.end());
	std::vector<int> dp(v.size(), 10 * n);
	int ans = 0;
	for (int i = 0; i < (int)(v.size()); ++i) {
		int pos = std::upper_bound(dp.begin(), dp.end(), v[i].second) - dp.begin();
		dp[pos] = v[i].second;
		ans = std::max(ans, pos + 1);
	}
	std::cout << n - ans << std::endl;
}
