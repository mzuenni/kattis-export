#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

using i64 = int64_t;

int main() {
	i64 n;
	cin >> n;
	vector<i64> t(n);
	for (i64& x : t)
		cin >> x;
	for (i64 i = 0; i < n; i++)
		t[i] -= i;
	auto sorted = t;
	sort(sorted.begin(), sorted.end());
	i64 res = 0;
	for (i64 x : t)
		res += abs(sorted[n/2] - x);
	cout << res << endl;
}
