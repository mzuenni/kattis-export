#include <bits/stdc++.h>
using namespace std;

const int K = 5;

int main() {
	int n; cin >> n;
	vector<pair<int,int>> intervals(n);
	for (auto &[a,b]: intervals) cin >> a >> b;
	sort(begin(intervals), end(intervals));
	
	// returns minimal j <= i such that intervals[j] and intervals[i] intersect
	auto find_intersecting = [&](int i) {
		int j = 0;
		while (intervals[j].second < intervals[i].first) j++;
		return j;
	};

	// returns maximal j < i such that intervals[j] and intervals[i] do not intersect (or -1)
	auto find_nonintersecting = [&](int i) {
		int j = i;
		while (j >= 0 && intervals[j].second >= intervals[i].first) j--;
		return j;
	};

	// dp[i][c] = minimal size of a dominating set of the first i intervals if c edge contractions are used
	vector<vector<int>> dp(n+1, vector<int>(K, n+1));
	dp[0][0] = 0;
	for (int i = 0; i < n; i++) {
		int j = i, k = i;
		for (int ec = 0; ec < K; ec++) {
			j = find_intersecting(j);
			k = find_nonintersecting(j);
			for (int c = ec; c < K; c++) {
				dp[i+1][c] = min(dp[i+1][c], dp[k+1][c-ec] + 1);
			}
		}
	}

	if (dp[n][0] > dp[n][K-1]) {
		int c = 1;
		while (dp[n][c] == dp[n][0]) c++;
		cout << c << endl;
	} else {
		cout << "impossible" << endl;
	}
}
