#include <iostream>
#include <vector>
#include <assert.h>
using namespace std;

int n, m, a, b;
vector<vector<int>> graph;
vector<int> cnt;
vector<bool> visited;

void dfs(int u) {
	assert (!visited[u]);
	visited[u] = true;
	cnt[u]++;
	for (int v: graph[u]) if (!visited[v]) {
		dfs(v);
	}
}

int main() {
	cin >> n >> m;
	graph.resize(n);
	cnt.resize(n);
	for (int i = 0; i < m; i++) {
		int a, b;
		cin >> a >> b;
		a--; b--;
		graph[a].push_back(b);
		graph[b].push_back(a);
	}
	cin >> a >> b;
	a--; b--;
	
	visited.assign(n, false);
	dfs(a);
	visited.assign(n, false);
	dfs(b);

	for (int i = 0; i < n; i++) if (cnt[i] >= 2) {
		cout << "yes" << endl << i+1 << endl;
		return 0;
	}
	cout << "no" << endl;
}
