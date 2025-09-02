#include <bits/stdc++.h>
using namespace std;

int main() {
	int n, s, r1, r2; // number of nodes, squirrel, raven 1, raven 2
	cin >> n >> s >> r1 >> r2;
	s--, r1--, r2--;

	vector<vector<int>> adj(n);
	for (int i = 1; i < n; i++) {
		int a, b;
		cin >> a >> b;
		a--, b--;
		adj[a].push_back(b);
		adj[b].push_back(a);
	}

	vector<int> deg(n); // node degree
	queue<int> q;
	for (int i = 0; i < n; i++) {
		deg[i] = adj[i].size();
		if (deg[i] == 1) q.push(i);
	}
	
	// leaf nodes have height 0
	// a node has height k if it becomes a leaf after removing all nodes of height < k

	vector<int> h(n); // height
	int c1, c2; // centers = nodes of maximal height, at most 2
	while (q.size()) {
		int i = q.front(); q.pop();
		c1 = c2, c2 = i;
		for (int j: adj[i]) if (--deg[j] == 1)
			h[j] = h[i]+1, q.push(j);
	}
	
	// the answer is the maximal height among the reachable nodes, plus 1
	// (the strategy of the squirrel is to always move to the "highest" node)

	vector<bool> reach(n);
	q.push(s);
	int hmax = 0; // maximal reachable height
	while (q.size()) {
		int i = q.front(); q.pop();
		if (i == r1 || i == r2) continue;
		reach[i] = true;
		hmax = max(hmax,h[i]);
		for (int j: adj[i]) if (!reach[j]) q.push(j);
	}
	
	// special case: need an extra turn if there are two centers
	//               and squirrel can reach both
	if (h[c1] == h[c2] && reach[c1] && reach[c2]) hmax++;
	
	cout << hmax+1 << endl;
}
