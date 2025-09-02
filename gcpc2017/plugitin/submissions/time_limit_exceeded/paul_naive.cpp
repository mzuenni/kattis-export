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
	
	int match = 0;
	for (int i = 0; i < m; i++) {
		pred.assign(n,-1);
		adj[m] = adj[m+1] = adj[i];
		match = max(match, max_matching(0,m+2));
	}
	cout << match << endl;
}
