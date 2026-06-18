#include <algorithm>
#include <iostream>
#include <vector>

const int MOD = 998244353;

int power(int a, int b) {
	int ans = 1;
	while (b) {
		if (b & 1) ans = 1LL * ans * a % MOD;
		a = 1LL * a * a % MOD;
		b >>= 1;
	}
	return ans;
}

int inverse(int a) {
	return power(a, MOD - 2);
}

int main() {
	int n;
	std::cin >> n;

	std::vector<std::pair<int, int>> songs(n);
	std::vector<int> all = {0, 1 << 30};

	for (auto& [a, b] : songs) {
		std::cin >> a >> b;
		all.push_back(a);
		all.push_back(b);
	}

	std::sort(all.begin(), all.end());
	all.erase(std::unique(all.begin(), all.end()), all.end());

	int m = all.size();

	for (auto& [a, b] : songs) {
		a = std::lower_bound(all.begin(), all.end(), a) - all.begin();
		b = std::lower_bound(all.begin(), all.end(), b) - all.begin();
	}

	std::vector<int> inv(n + 1);

	for (int i = 1; i <= n; ++i) {
		inv[i] = inverse(i);
	}

	std::vector<std::vector<int>> vecL(m), vecR(m);

	for (int i = 0; i < n; ++i) {
		auto [a, b] = songs[i];
		vecL[std::min(a - 1, b)].push_back(i);
		vecR[std::max(a + 1, b)].push_back(i);
	}

	// let S(l, r) be the set of cards (a, b) with l < a < r and l <= b <= r
	// dp[l][r]    = expected timeline length if we only consider cards in S(l, r)
	// sumLA[l][r] = sum of dp[l][a] over all cards (a, b) in S(l, r)
	// sumAR[l][r] = sum of dp[a][r] over all cards (a, b) in S(l, r)
	// cnt[l][r]   = |S(l, r)|
	std::vector dp(m, std::vector<int>(m, 0));
	std::vector sumLA(m, std::vector<int>(m, 0));
	std::vector sumAR(m, std::vector<int>(m, 0));
	std::vector cnt(m, std::vector<int>(m, 0));

	for (int len = 2; len < m; ++len) {
		for (int l = 0, r = len; r < m; ++l, ++r) {
			sumLA[l][r] = sumLA[l][r - 1];
			sumAR[l][r] = sumAR[l + 1][r];
			cnt[l][r] = cnt[l][r - 1];
			for (int i : vecR[r]) {
				auto [a, b] = songs[i];
				if (l < a && a < r && l <= b && b <= r) {
					sumLA[l][r] = (sumLA[l][r] + dp[l][a]) % MOD;
					cnt[l][r] += 1;
				}
			}
			for (int i : vecL[l]) {
				auto [a, b] = songs[i];
				if (l < a && a < r && l <= b && b <= r) {
					sumAR[l][r] = (sumAR[l][r] + dp[a][r]) % MOD;
				}
			}
			dp[l][r] = (1LL * cnt[l][r] + sumLA[l][r] + sumAR[l][r]) * inv[cnt[l][r]] % MOD;
		}
	}

	std::cout << dp[0][m - 1] << '\n';

	return 0;
}

