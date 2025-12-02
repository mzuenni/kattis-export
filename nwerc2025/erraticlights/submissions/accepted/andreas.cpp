#include <iostream>
#include <vector>
#include <algorithm>
#include <map>
#include <iomanip>
using namespace std;

map<tuple<int, int, int>, double> dp;
double rec(int a, int b, int c) {
	if (dp.find({a, b, c}) != dp.end())
		return dp[{a, b, c}];
	if (b == 0) return 0;
	if (a > 0) {
		/*
		          a = (1/3) * (1+a) + (1/3) * (1+b) * (1/3) * (1+c)
		<=> (2/3) a = (1/3) * (3+b+c)
		<=>       a = (3/2) + (1/2) * (b+c)
		*/
		vector<vector<int>> new_states = { { a-1, b+1, c }, { a-1, b, c+1 } };
		sort(new_states[0].begin(), new_states[0].end());
		sort(new_states[1].begin(), new_states[1].end());
		dp[{a, b, c}] = 1.5 + 0.5 * (rec(new_states[0][0], new_states[0][1], new_states[0][2])
			+ rec(new_states[1][0], new_states[1][1], new_states[1][2]));
	} else {
		/*
		          b = (2/3) * (1+b) + (1/3) * (1+c)
		<=> (1/3) b = (2/3) + (1/3) * (1+c)
		<=>       b = 3 + c
		*/
		dp[{a, b, c}] = 3 + rec(a, b-1, c+1);
	}
	return dp[{a, b, c}];
}

int main() {
	cin.tie(0);
	ios_base::sync_with_stdio(0);

	int n;
	string s;
	cin >> n >> s;
	string cs = "rgb";
	vector<int> nums(3);
	for (char c: s) nums[cs.find(c)]++;
	sort(nums.begin(), nums.end());
	cout << fixed << setprecision(10) << rec(nums[0], nums[1], nums[2]) << '\n';
}