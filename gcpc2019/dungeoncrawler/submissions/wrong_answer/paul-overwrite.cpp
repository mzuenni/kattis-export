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

	void finalize() {
		set<string> items;
		for (int i = 1; i <= n; i++) {
			if (item[i] == "") at = 0;
			items.insert(item[i]);
		}
		if ((int)items.size() != n) at = 0;
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
	
	bool any_ok = false;
	for (int i = 1; i <= n; i++) any_ok |= st[i].at != 0;
	if (!any_ok) {
		cout << "R no" << endl;
		exit(0);
	}

	if (visited.count(it)) return;
	visited.insert(it);

	for (char c: dirs) {
		cout << "W " << c << endl;
		for (int i = 1; i <= n; i++) st[i].move(c);
		dfs();
		cout << "W " << c << endl;
		for (int i = 1; i <= n; i++) st[i].move(c);
		cin >> it >> dirs;
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

	for (int i = 1; i <= n; i++) st[i].finalize();

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
