#include <bits/stdc++.h>
using namespace std;

int main() {
	int n, k;
	cin >> n >> k;
	vector<int> cost(n);
	for (int i = 0; i < n; i++) {
		int mine; cin >> mine;
		vector<int> their(k-1);
		for (int &his: their) cin >> his;
		
		int bribe_min = -1, bribe_max = accumulate(begin(their),end(their),0);
		while (bribe_max - bribe_min > 1) {
			int bribe = (bribe_min + bribe_max) / 2;
			int sum = 0;
			for (int his: their) sum += max(0, his - (mine+bribe-1));
			if (sum <= bribe) bribe_max = bribe;
			else bribe_min = bribe;
		}
		cost[i] = bribe_max;
	}
	sort(begin(cost),end(cost));
	cout << accumulate(begin(cost),begin(cost)+(n/2+1),0) << endl;
}
