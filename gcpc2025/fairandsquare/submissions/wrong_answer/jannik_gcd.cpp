#include <algorithm>
#include <iostream>
#include <numeric>
#include <vector>

using namespace std;

#define all(a) (a).begin(), (a).end()

template <typename F>
int lgcd(F&& f, int n, int res)
{
	int i = 0;
	while (i < n) {
		while (i < n and f(i) == '.') i++;
		if (i >= n) continue;
		int x = 0;
		while (i < n and f(i) == '#') i++, x++;
		res = gcd(res, x);
	}
	return res;
}

int main()
{
	int h, w;
	cin >> h >> w;
	vector<string> grid(h);
	int res = 0;
	for (auto& s : grid) {
		cin >> s;
		res += count(all(s), '#');
	}

	for (int i = 0; i < h; i++)
		res = lgcd([&](int j) { return grid[i][j]; }, w, res);
	for (int j = 0; j < w; j++)
		res = lgcd([&](int i) { return grid[i][j]; }, h, res);

	cout << res << endl;
}
