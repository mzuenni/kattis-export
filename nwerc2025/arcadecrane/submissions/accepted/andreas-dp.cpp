#include <iostream>
#include <algorithm>
#include <numeric>
#include <queue>
#include <map>
#include <vector>
#include <assert.h>
using namespace std;

const int N = 5000;

vector<int> sorting_op(vector<int> a, int old_idx, int new_idx) {
	vector<int> elements(a.begin() + old_idx, a.begin() + old_idx + 3);
	a.erase(a.begin() + old_idx, a.begin() + old_idx + 3);
	a.insert(a.begin() + new_idx, elements.begin(), elements.end());
	return a;
}

vector<tuple<int, int, int, int>> dp;
vector<vector<int>> permutations;
map<vector<int>, int> perm_idx;
void precompute_DP(int n) {
	vector<int> numbers(5);
	iota(numbers.begin(), numbers.end(), n - 5);
	int s = 0;
	do {
		permutations.push_back(numbers);
		perm_idx[numbers] = s++;
	} while (next_permutation(numbers.begin(), numbers.end()));

	// state: min_number_of_sorting_ops, original_index, next_index, previous_permutation_index
	dp.assign(120, {N+30, -1, -1, -1});
	queue<pair<int, int>> q;
	dp[0] = {0, -1, -1, -1};
	q.emplace(0, 0);
	while (!q.empty()) {
		auto [value, cur_perm_idx] = q.front();
		q.pop();

		for (int i = 0; i < 3; i++) for (int j = 0; j < 3; j++) {
			vector<int> after_sort = sorting_op(permutations[cur_perm_idx], i, j);
			int nxt_perm_idx = perm_idx[after_sort];
			if (get<0>(dp[nxt_perm_idx]) <= value + 1) continue;
			dp[nxt_perm_idx] = {value + 1, j, i, cur_perm_idx};
			q.emplace(value + 1, nxt_perm_idx);
		}
	}
}

int main() {
	cin.tie(0);
	ios_base::sync_with_stdio(0);

	int n;
	cin >> n;
	vector<int> a(n), pos(n);
	for (int i = 0; i < n; i++) {
		cin >> a[i];
		a[i]--;
		pos[a[i]] = i;
	}

	precompute_DP(n);
	vector<pair<int, int>> sol;

	// sort all integers up to the last three with insertion sort
	for (int smallest_wrong = 0; smallest_wrong < n - 3; smallest_wrong++) while (smallest_wrong != a[smallest_wrong]) {
		int right_index = min(pos[smallest_wrong], n - 3);
		sol.emplace_back(right_index, smallest_wrong);
		a = sorting_op(a, right_index, smallest_wrong);
		for (int i = 0; i < n; i++) pos[a[i]] = i;
	}

	// sort the last five integers with precomputed DP
	vector<int> cur_perm(a.end() - 5, a.end());
	while (cur_perm != vector<int>{n - 5, n - 4, n - 3, n - 2, n - 1}) {
		auto [value, left_idx, right_idx, nxt_perm_idx] = dp[perm_idx[cur_perm]];
		sol.emplace_back(left_idx + n - 5, right_idx + n - 5);
		a = sorting_op(a, left_idx + n - 5, right_idx + n - 5);
		cur_perm = permutations[nxt_perm_idx];
	}

	vector<int> sorted(n);
	iota(sorted.begin(), sorted.end(), 0);
	assert (a == sorted);

	cout << sol.size() << '\n';
	for (auto [a, b]: sol) {
		cout << a + 1 << ' '<< b + 1 << '\n';
	}
}
