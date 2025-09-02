#include <bits/stdc++.h>
using namespace std;

const int MAX_EDGES = 26;

vector<string> artifacts = {
	"fountain", "obelisk", "crystals", "cauldron", "shrine", "weapons", "sword", "holygrail", "ring", "scepterofawesomeness", "mightydagger", "bootsofswiftness"
};

struct Graph {
	int n;
	int current;
	vector<vector<int>> adj;
	vector<string> adjS;
	Graph() : n(0), current(0), adj(), adjS() {}
	Graph(int _n, int _current) : n(_n), current(_current),
		adj(n, vector<int>(MAX_EDGES, -1)), adjS(n) {}
	
	void initS() {
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < MAX_EDGES; j++) {
				if (adj[i][j] != -1) adjS[i] += (char) ('A'+j);
			}
		}
	}
	
	pair<bool,string> go(char c) {
		if (c < 'A' || c >= 'A' + MAX_EDGES) return {false, "Invalid Path Name"};
		if (adj[current][c-'A'] == -1) return {false, "Path nonexistent"};
		current = adj[current][c-'A'];
		return {true, ""};
	}
	
	void printCurrent(ostream & os) {
		string s = adjS[current];
		random_shuffle(s.begin(), s.end());
		os << artifacts[current] << " " << s << endl;
	}
};
