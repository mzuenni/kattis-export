#include <bits/stdc++.h>
using namespace std;

#define xx first
#define yy second

int main() {
	int n, m; cin >> n >> m;
	vector<vector<pair<int,char>>> adj(n);
	vector<vector<int>> cnt(n,vector<int>(26));
	while (m--) {
		int a, b; char c;
		cin >> a >> b >> c;
		a--, b--;
		adj[a].emplace_back(b,c);
		cnt[a][c-'A']++;
		adj[b].emplace_back(a,c);
		cnt[b][c-'A']++;
	}
	string s; cin >> s;
	
	vector<pair<double,bool>> p(n);
	p[0] = {1,true};
	for (char c : s) {
		vector<pair<double,bool>> np(n);
		np[n-1] = p[n-1];
		for (int i = 0; i < n-1; i++) if (p[i].yy) {
			if (cnt[i][c-'A']) {
				for (auto e : adj[i]) if (e.yy == c) {
					np[e.xx].xx += p[i].xx/cnt[i][c-'A'], np[e.xx].yy = true;
				}
			} else {
				np[i].xx += p[i].xx, np[i].yy = true; 
			}
		}
		p = np;
	}
	cout << fixed << setprecision(12) << 100*p[n-1].xx << endl;
}
