#include <bits/stdc++.h>
using namespace std;

int L, R, k;
vector<vector<int>> adj;
vector<int> matchL, matchR;
vector<int> depth;

bool bfs(int from, int to) {
	depth.assign(L+1,INT_MAX);
	queue<int> q;
	for (int i = from; i < to; i++) if (matchL[i] == R) {
		depth[i] = 0; q.push(i);
	}
	while (!q.empty()) {
		int i = q.front(); q.pop();
		if (depth[i] >= depth[L]) continue;
		for (const auto &j : adj[i]) {
			if (depth[matchR[j]] == INT_MAX) {
				depth[matchR[j]] = depth[i] + 1;
				q.push(matchR[j]);
			}
		}
	}
	return depth[L] < INT_MAX;
}

bool dfs(int i) {
	if (i == L) return true;
	for (const auto &j : adj[i]) {
		if (depth[matchR[j]] == depth[i] + 1 && dfs(matchR[j])) {
			matchL[i] = j; matchR[j] = i; return true;
		}
	}
	depth[i] = INT_MAX;
	return false;
}

int max_matching(int from, int to) {
	int res = 0;
	while (bfs(from,to)) {
		for (int i = from; i < to; i++) {
			if (matchL[i] == R && dfs(i)) res++;
		}
	}
	return res;
}

int main() {
	int m, n;
	cin >> m >> n >> k;
	L = m+2, R = n;

	adj.resize(m+2);
	matchL.resize(L,R);
	matchR.resize(R,L);

	while (k--) {
		int a, b; cin >> a >> b;
		adj[a-1].push_back(b-1);
	}
	
	int match_base = max_matching(0,m), match_extra = 0;
	vector<int> old_matchL = matchL, old_matchR = matchR;

	for (int i = 0; i < m; i++) {
		matchL = old_matchL, matchR = old_matchR;
		adj[m] = adj[m+1] = adj[i];
		match_extra = max(match_extra, max_matching(m,m+2));
	}
	cout << match_base + match_extra << endl;
}
