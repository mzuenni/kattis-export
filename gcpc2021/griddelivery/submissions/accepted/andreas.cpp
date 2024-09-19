#include <iostream>
#include <set>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
	cin.tie(0);
	ios_base::sync_with_stdio(0);

	int h, w;
	cin >> h >> w;

	multiset<int> heights;
	vector<pair<int, int> > coins;
	for (int i = 0; i < h; i++) {
		string s; cin >> s;
		for (int j = 0; j < w; j++) if (s[j] == 'C')
			coins.emplace_back(j, i);
	}
	sort(coins.begin(), coins.end());

	int res = 0;
	for (auto [x,y]: coins) {
		auto it = heights.lower_bound(-y);
		if (it == heights.end()) {
			res++;
		} else {
			heights.erase(it);
		}
		heights.insert(-y);
	}
	cout << res << '\n';
}
