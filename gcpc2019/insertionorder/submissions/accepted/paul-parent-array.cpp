#include <bits/stdc++.h>
using namespace std;

int h(int n) {
	return 32 - __builtin_clz(n);
}

int main() {
	int n, k;
	cin >> n >> k;
	
	for (int m = 1; m <= n; m++) {
		if (h(m) + n-m != k) continue;

		vector<vector<int>> children(n);
		for (int i = 1; i < n; i++) {
			int p = i < m ? (i-1)/2 : i-1;
			children[p].push_back(i);
		}

		int offset = 0;
		vector<pair<int,int>> nodes;
		function<void(int,int)> rec = [&](int i, int depth) {
			int deg = children[i].size();
			if (deg >= 1) rec(children[i][0], depth+1);
			nodes.emplace_back(depth, ++offset);
			if (deg >= 2) rec(children[i][1], depth+1);
		};

		rec(0,0);
		sort(begin(nodes), end(nodes));
		
		for (int i = 0; i < n; i++) {
			cout << nodes[i].second << " \n"[i+1==n];
		}
		return 0;
	}
	cout << "impossible" << endl;
}
