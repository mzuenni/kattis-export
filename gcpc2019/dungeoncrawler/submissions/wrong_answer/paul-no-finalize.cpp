#include <bits/stdc++.h>
using namespace std;

const int N = 1010;
int n;

struct state {
	int at = 0;
	int adj[N][26] = {};
	int adjmask[N] = {};
	string item[N];

	void check(string it, int itmask) {
		if (item[at] == "") item[at] = it;
		if (item[at] != it) at = 0;
		if (adjmask[at] != itmask) at = 0;
	}
	
	void move(char c) {
		at = adj[at][c-'A'];
	}
};

state st[N];
set<string> visited;

void dfs() {
	string it; cin >> it;
	
	int itmask = 0;
	string dirs; cin >> dirs;
	for (char c: dirs) itmask |= 1 << (c-'A');
	
	for (int i = 1; i <= n; i++) st[i].check(it,itmask);

	if (visited.count(it)) return;
	visited.insert(it);

	for (char c: dirs) {
		cout << "W " << c << endl;
		for (int i = 1; i <= n; i++) st[i].move(c);
		dfs();
		cout << "W " << c << endl;
		for (int i = 1; i <= n; i++) st[i].move(c);
		string foo;
		cin >> foo >> foo;
	}
}

int main() {
	cin >> n;
	state graph;
	for (int i = 1; i <= n; i++) {
		int k; cin >> k;
		while (k--) {
			char c; cin >> c;
			int j; cin >> j;
			graph.adj[i][c-'A'] = j;
			graph.adjmask[i] |= 1 << (c-'A');
		}
	}
	
	for (int i = 1; i <= n; i++) {
		st[i] = graph, st[i].at = i;
	}
	
	dfs();

	cout << "R ";

	int res = 0;
	for (int i = 1; i <= n; i++) {
		if (st[i].at == 0) continue;
		if (res != 0) {
			cout << "ambiguous" << endl;
			return 0;
		}
		res = i;
	}
	
	if (res != 0) cout << res << endl;
	else cout << "no" << endl;
}
