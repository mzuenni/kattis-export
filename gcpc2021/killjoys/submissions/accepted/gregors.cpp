#include <iostream>
#include <vector>
#include <queue>
using namespace std;

int main() {
	int n,m,p; cin >> n >> m >> p;
	vector<vector<int>> g(n);
	for (int i = 0; i < m; ++i) {
		int a,b; cin >> a >> b;
		a--; b--;
		g[a].push_back(b);
		g[b].push_back(a);
	}
	vector<int> proc(n,-1);
	int comp = 0;
	for (int i = 0; i < n; ++i) {
		if (proc[i] != -1) continue;
		comp++;
		proc[i] = 0;
		queue<int> q; q.push(i);
		while (!q.empty()) {
			int x = q.front(); q.pop();
			for (int k : g[x]) {
				if (proc[k] == -1) {
					proc[k] = proc[x]^1;
					q.push(k);
				}
				else if (proc[k] == proc[x]) {
					cout << "impossible" << endl;
					return 0;
				}
			}
		}
	}
	int res = 1;
	for (int i = 0; i < comp-1; ++i) res = res * 2 % p;
	cout << (res+1) % p << endl;
}
