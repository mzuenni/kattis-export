#include <iostream>
#include <vector>
#include <assert.h>
using namespace std;

int n, m, a, b;
vector<vector<int>> graph;

bool dfs(int u, int meeting_point, vector<bool> &vis) {
	assert (!vis[u]);
	vis[u] = true;
	if (u == meeting_point) return true;
	for (int v: graph[u]) if (!vis[v]) {
		if (dfs(v, meeting_point, vis)) return true;
	}
	return false;
}

int main() {
	cin >> n >> m;
	graph.resize(n);
	for (int i = 0; i < m; i++) {
		int a, b;
		cin >> a >> b;
		a--; b--;
		graph[a].push_back(b);
	}
	cin >> a >> b;
	a--; b--;
	
	for (int i = 0; i < n; i++) {
		vector<bool> vis1(n, false), vis2(n, false);
		if (dfs(a, i, vis1) && dfs(b, i, vis2)) {
			cout << "yes" << endl << i+1 << endl;
			return 0;
		}
	}
	cout << "no" << endl;
}
