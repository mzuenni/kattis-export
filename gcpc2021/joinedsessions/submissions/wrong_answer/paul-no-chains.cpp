#include <bits/stdc++.h>
using namespace std;

const int K = 5;

int main() {
	int n; cin >> n;
	vector<pair<int,int>> intervals(n);
	for (auto &[a,b]: intervals) cin >> a >> b;
	sort(begin(intervals), end(intervals));
	
	vector<pair<int,int>> events;
	for (int i = 0; i < n; i++) {
		auto [a,b] = intervals[i];
		events.emplace_back(a,~i);
		events.emplace_back(b,i);
	}
	sort(begin(events), end(events));

	// f[i] = minimal j <= i such that intervals[j] and intervals[i] intersect
	// g[i] = maximal j < i such that intervals[j] and intervals[i] do not intersect (or -1)
	vector<int> f(n), g(n);

	set<int> active, inactive;
	for (auto [x,i]: events) { x = x;
		if (i < 0) {
			i = ~i;
			active.insert(i);
			f[i] = *begin(active);
			g[i] = inactive.empty() ? -1 : *rbegin(inactive);
		} else {
			active.erase(i);
			inactive.insert(i);
		}
	}

	// dp[i][c] = minimal size of a dominating set of the first i intervals if c edge contractions are used
	vector<vector<int>> dp(n+1, vector<int>(K, n+1));
	dp[0][0] = 0;
	for (int i = 0; i < n; i++) {
		int j = i, k = i;
		// only considers unions of pairs of intervals but not longer chains, this fails on some cases
		for (int ec = 0; ec < 2; ec++) {
			j = f[j], k = g[j];
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
