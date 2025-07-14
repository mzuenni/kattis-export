#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

#define all(a) (a).begin(), (a).end()

int main()
{
	int h, w;
	cin >> h >> w;
	vector<string> grid(h);
	int area = 0;
	for (auto& s : grid) {
		cin >> s;
		area += count(all(s), '#');
	}
	int res = 1;

	for (int x = 2; x <= min({ h, w, area }); x++) {
		if (area % (x*x))
			continue;
		auto g = grid;
		for (int i = 0; i < h; i++)
			for (int j = 0; j < w; j++) {
				if (g[i][j] != '#')
					continue;
				if (i + x > h or j + x > w)
					goto nope;
				for (int ii = i; ii < i + x; ii++)
					for (int jj = j; jj < j + x; jj++) {
						if (g[ii][jj] != '#')
							goto nope;
						g[ii][jj] = '.';
					}
			}
		res = x;
	nope:;
	}

	cout << res << endl;
}
