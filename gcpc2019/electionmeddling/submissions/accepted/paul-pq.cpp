#include <bits/stdc++.h>
using namespace std;

int main() {
	int n, m;
	cin >> n >> m;

	vector<int> cost(n);
	for (int i = 0; i < n; i++) {
		int x; cin >> x;

		priority_queue<int> Q;
		for (int j = 0; j < m-1; j++) {
			int y; cin >> y;
			Q.push(y);
		}

		while (x <= Q.top()) {
			x++, cost[i]++;
			Q.push(Q.top()-1);
			Q.pop();
		}
	}

	sort(begin(cost),end(cost));
	cout << accumulate(begin(cost),begin(cost)+(n/2+1),0) << endl;
}
