#include <bits/stdc++.h>

using namespace std;

/**
 * This validator assumes that validate.ctd is successful
 * -> it does not check the correct layout and constraints
 * only highlevel graph properties are checked
 */
 

bool readGraph(int n) {
	vector<map<char, int>> map(n);
	// read
	for (int i = 0; i < n; i++) {
		int k;
		cin >> k;
		if (k < 1 || k > 26) {
			cerr << "invalid number of edges" << endl;
		}
		for (int j = 0; j < k; j++) {
			char c;
			int m;
			cin >> c >> m;
			if (c < 'A' || c > 'Z') {
				cerr << "Invalid edge type " << c << endl;
				return false;
			}
			if (map[i].find(c) != map[i].end()) {
				cerr << "Duplicate edge type found in line " << i+1 << endl;
				return false;
			}
			if (m < 1 || m > n) {
				cerr << "Invalid target " << m << endl;
				return false;
			}
			if (m-1 == i) {
				cerr << "Self loop detected in line " << i+1 << endl;
				return false;
			}
			// verify reverse edge if target node was already processed
			if (m-1 < i) {
				if (map[m-1].find(c) == map[m-1].end()) {
					cerr << "Reverse edge not existent between " << i+1 << " and " << m << endl;
					return false;
				}
				if (map[m-1][c] != i) {
					cerr << "Reverse edge is invalid between " << i+1 << " and " << m << endl;
					return false;
				}
			}
			map[i][c] = m-1;
		}
	}
	// verify connected
	vector<bool> vis(n);
	vector<int> todo;
	todo.push_back(0);
	vis[0] = true;
	int visited = 1;
	while (todo.size()) {
		int cur = *todo.rbegin();
		todo.pop_back();
		for (auto & p : map[cur]) {
			if (!vis[p.second]) {
				visited++;
				vis[p.second] = true;
				todo.push_back(p.second);
			}
		}
	}
	if (visited != n) {
		cerr << "Graph is not connected" << endl;
		return false;
	}
	return true;
}

int main() {
	string sep;
	cin >> sep;
	if (sep == "--Level:infinite--") {
		// directly go to Map
	} else if (sep == "--Level--") {
		int n, pos;
		cin >> n >> pos;
		if (pos < 1 || pos > n) {
			cerr << "Pos " << pos << " not valid with " << n << " nodes" << endl;
			return 43;
		}
		if (!readGraph(n)) return 43;
	} else {
		cerr << "Level header line is invalid" << endl;
		return 43;
	}
	cin >> sep;
	if (sep != "---Map---") {
		cerr << "Map header line is invalid" << endl;
		return 43;
	}
	int n;
	cin >> n;
	if (!readGraph(n)) return 43;
	return 42;
}
