#include <bits/stdc++.h>
using namespace std;

int m, n, k;
vector<vector<int>> adj;
vector<int> pred;
vector<bool> mark;

bool find_match(int i) {
	if (i == -1) return true;
	for (const int &j: adj[i]) {
		if (mark[j]) continue;
		mark[j] = true;
		if (find_match(pred[j])) {
			pred[j] = i;
			return true;
		}
	}
	return false;
}

int max_matching(int from, int to) {
	int res = 0;
	for (int i = from; i < to; i++) {
		mark.assign(n,false);
		if (find_match(i)) res++;
	}
	return res;
}

int main() {
	cin >> m >> n >> k;
	
	adj.resize(m+2);
	pred.resize(n,-1);

	while (k--) {
		int a, b; cin >> a >> b;
		adj[a-1].push_back(b-1);
	}
	
	int match_base = max_matching(0,m), match_extra = 0;
	vector<int> old_pred = pred;

	for (int i = 0; i < m; i++) {
		pred = old_pred;
		adj[m] = adj[m+1] = adj[i];
		match_extra = max(match_extra, max_matching(m,m+2));
	}
	cout << match_base + match_extra << endl;
}
