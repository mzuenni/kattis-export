#include <bits/stdc++.h>
using namespace std;

bool intersect(pair<int,int> p, pair<int,int> q) {
	auto [a,b] = p;
	auto [c,d] = q;
	return max(a,c) <= min(b,d);
}

int dominating_set(vector<pair<int,int>> intervals) {
	int n = intervals.size(), res = n;
	for (int mask = 0; mask < (1 << n); mask++) {
		int cur = __builtin_popcount(mask);
		if (cur >= res) continue;
		
		bool is_dom = true;
		for (int i = 0; i < n; i++) {
			bool ok = false;
			for (int j = 0; j < n; j++) if (mask & (1 << j)) {
				if (intersect(intervals[i], intervals[j])) ok = true;
			}
			is_dom = is_dom && ok;
		}
		if (is_dom) res = cur;
	}
	return res;
}

bool connected(vector<pair<int,int>> intervals) {
	sort(begin(intervals), end(intervals));
	for (int i = 0; i+1 < int(intervals.size()); i++) {
		if (intervals[i].second < intervals[i+1].first) return false;
	}
	return true;
}

bool rec(vector<pair<int,int>> intervals, int dom, int max_depth) {
	if (max_depth > 0) {
		int n = intervals.size();

		for (int i = 0; i < n; i++) {
			for (int j = i+1; j < n; j++) {
				if (!intersect(intervals[i], intervals[j])) continue;

				vector<pair<int,int>> new_intervals;
				for (int k = 0; k < n; k++) {
					if (k != i && k != j) new_intervals.push_back(intervals[k]);
				}

				auto [a,b] = intervals[i];
				auto [c,d] = intervals[j];
				new_intervals.emplace_back(min(a,c), max(b,d));

				if (rec(new_intervals, dom, max_depth-1)) return true;
			}
		}
		return false;
	} else {
		return dominating_set(intervals) < dom;
	}
}

int solve(vector<pair<int,int>> intervals) {
	int dom = dominating_set(intervals);
	if (dom == 1) return -1;
	for (int res = 1; res <= 3; res++) {
		if (rec(intervals, dom, res)) return res;
	}
	return -1;
}

vector<pair<int,int>> generate() {
	while (true) {
		int n = 5 + rand() % 10;
		vector<int> p(2*n);
		iota(begin(p), end(p), 0);
		random_shuffle(begin(p), end(p));

		vector<pair<int,int>> intervals(n);
		for (int i = 0; i < n; i++) {
			int x = p[i], y = p[n+i];
			if (x > y) swap(x,y);
			intervals[i] = {x,y};
		}
		
		if (connected(intervals) && dominating_set(intervals) > 1) return intervals;
	}
}

int main() {
	int n; cin >> n;
	vector<pair<int,int>> intervals(n);
	for (auto &[a,b]: intervals) cin >> a >> b;
	int res = solve(intervals);
	if (res != -1) cout << res << endl;
	else cout << "impossible" << endl;
}
