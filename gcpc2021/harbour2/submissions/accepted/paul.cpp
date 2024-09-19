#include <bits/stdc++.h>
using namespace std;

int main() {
	int n, s, t;
	cin >> n >> s >> t;

	vector<int> a(n+1);
	for (int i = 0; i < s; i++) cin >> a[i];
	for (int i = 0; i < t; i++) cin >> a[n-i];

	vector<int> pos(n+1);
	set<pair<int,int>> parcels;
	for (int i = 0; i <= n; i++) {
		pos[a[i]] = i;
		parcels.emplace(i,a[i]);
	}

	int res = a[s-1] == 0 || a[s] == 0;
	for (int i = 1; i <= n; i++) {
		auto it = parcels.find({pos[i],i});
		if (it != begin(parcels) && prev(it)->second == 0) res++;
		if (next(it) != end(parcels) && next(it)->second == 0) res++;
		parcels.erase(it);
	}
	cout << res << endl;
}
