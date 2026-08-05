//Author: Stefan Toman

#include <iostream>
#include <unordered_set>
#include <vector>
#include <queue>

using namespace std;

int main() {
	int n, m;
	cin >> n >> m;
	vector< unordered_set<int> > c(n);
	for(int i = 0; i < m; i++) {
		int a, b;
		cin >> a >> b;
		c[a-1].insert(b-1);
	}
	while(true) {
		int max = 0;
		for(int i = 1; i < n; i++) if(c[i].size() > c[max].size()) max = i;
		vector<int> p(n, -1);
		queue<int> q;
		q.push(max);
		bool breaking = false;
		while(!q.empty() && !breaking) {
			for(auto t: c[q.front()]) {
				if(c[t].size()+2 <= c[max].size()) {
					p[t] = q.front();
					int h = t;
					while(h != max) {
						c[p[h]].erase(h);
						c[h].insert(p[h]);
						h = p[h];
					}
					breaking = true;
					break;
				}
				if(p[t] == -1) {
					p[t] = q.front();
					q.push(t);
				}
			}
			q.pop();
		}
		if(!breaking) {
			cout << c[max].size() << endl;
			return 0;
		}
	}
}
