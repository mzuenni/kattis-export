#include <bits/stdc++.h>
using namespace std;

int main() {
	int h, w;
	cin >> h >> w;

	vector<string> a(h);
	for (string &s: a) cin >> s;

	auto find_next = [&](int ci, int cj) -> pair<int,int> {
		for (int i = ci; i < h; i++) {
			for (int j = cj; j < w; j++) {
				if (a[i][j] == 'C') return {i,j};
			}
		}
		return {-1,-1};
	};
	
	int res = 0;
	while (true) {
		auto [ci,cj] = find_next(0,0);
		if (ci == -1) break;
		res++;
		while (ci != -1) {
			a[ci][cj] = '_';
			tie(ci,cj) = find_next(ci,cj);
		}
	}
	cout << res << endl;
}
