#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

vector<int> solve(int n, int a, int b)
{
	vector<int> res;
	for (int i = n - a + 1; i < n; i++)
		res.emplace_back(i);
	for (int i = 1; i <= n - (a + b - 1); i++)
		res.emplace_back(i);
	res.emplace_back(n);
	for (int i = n - a; i > n - a - b + 1; i--)
		res.emplace_back(i);
	return res;
}

int main() {
	int n, a, b;
	cin >> n >> a >> b;
	if (a + b - 1 > n or max(a,b) == 1) {
		cout << "no\n";
		return 0;
	}
	cout << "yes\n";
	auto res = solve(n, max(a,b), min(a,b));
	if (a > b)
		reverse(res.begin(), res.end());
	for (auto i = res.size(); i-- > 0; )
		cout << res[i] << (i ? ' ' : '\n');
}
