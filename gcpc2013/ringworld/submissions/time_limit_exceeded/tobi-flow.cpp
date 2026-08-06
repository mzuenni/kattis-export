// @EXPECTED_RESULTS@: TIMELIMIT
#include <iostream>
#include <map>
#include <algorithm>

using namespace std;
#define FOR(i,a,b) for (int i = (a); i < (b); i++)
#define add(a,b) ranges[cnt++] = make_pair(a,b)

pair<int,int> adj[100005];
map<int,int> pre;
map<int,bool> mark;
int numCases, m, n;

bool find_match(int x) {
	if (x == 0) return true;
	x--;
	int s = adj[x].first;
	int e = adj[x].second;
	if (s > e) e += m;
	FOR(i, s, e+1) {
		int next = i%m;
		if (mark[next]) continue;
		mark[next] = true;
		if (find_match(pre[next])) {
			pre[next] = x + 1;
			return true;
		}
	}
	return false;
}

int max_match() {
	pre.clear();
	int matching = 0;
	FOR(i, 0, n) {
		mark.clear();
		if (find_match(i+1)) matching++;
	}
	return matching;
}

int main() {
	cin >> numCases;
	while (numCases --> 0) {
		cin >> m >> n;
		FOR(i, 0, n) cin >> adj[i].first >> adj[i].second;
		cout << ((max_match() == n) ? "YES" : "NO") << endl;
	}
	return 0;
}
