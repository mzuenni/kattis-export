//Author: Stefan Toman

#include <iostream>
#include <map>
#include <vector>
#include <queue>

using namespace std;

int main() {
	int n, m, l, t = 0;
	cin >> n >> m >> l;
	vector< map<int, int> > conn(n);
	for(int i = 0; i < m; i++) {
		int a, b, c;
		cin >> a >> b >> c;
		if(conn[a-1][b-1] == 0 || conn[a-1][b-1] > c) conn[a-1][b-1] = c;
		if(conn[b-1][a-1] == 0 || conn[b-1][a-1] > c) conn[b-1][a-1] = c;
		if(i < l) t += c;
	}
	vector<bool> seen(n, false);
	priority_queue< pair<int, int> > q;
	q.push(make_pair(0, 0));
	int mst = 0, nodes = 0;
	while(!q.empty() && nodes < n) {
		if(!seen[q.top().second]) {
			seen[q.top().second] = true;
			mst += q.top().first;
			nodes++;
			for(auto next: conn[q.top().second]) {
				if(!seen[next.first]) {
					q.push(make_pair(-next.second, next.first));
				}
			}
		}
		q.pop();
	}
	cout << (-mst <= t && nodes == n ? "" : "im") << "possible" << endl;
	return 0;
}
