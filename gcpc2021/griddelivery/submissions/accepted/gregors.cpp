#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
	int h,w; cin >> h >> w;
	vector<vector<int>> field(w, vector<int>{0});
	vector<int> height(w);
	for (int i = 0; i < h; ++i) {
		for (int j = 0; j < w; ++j) {
			char c; cin >> c;
			if (c == 'C') {
				field[j].push_back(i+1);
				height[j] = i+1;
			}
		}
	}
	int res = 0;
	int col = 0;
	while (true) {
		while (col < w && height[col] == 0) col++;
		if (col == w) break;
		res++;
		int h = 0;
		for (int i = col; i < w; ++i) {
			if (height[i] >= h) {
				int ch = h == 0 ? 0 : *--lower_bound(field[i].begin(), field[i].end(), h);
				h = height[i];
				height[i] = ch;
			}
		}		
	}
	cout << res << endl;
}
