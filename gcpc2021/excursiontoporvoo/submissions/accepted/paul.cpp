#include <bits/stdc++.h>
using namespace std;

int main() {
	int n, m;
	cin >> n >> m;
	
	vector<tuple<int,int,int>> edges(m);
	for (auto &[c,d,i]: edges) cin >> i >> d >> c;
	
	int q; cin >> q;
	vector<pair<int,int>> cars(q);
	for (int j = 0; j < q; j++) {
		cin >> cars[j].first, cars[j].second = j;
	}
	
	vector<long long> best(n,1e12), res(q);
	long long sum = (n-1) * (long long)1e12;

	sort(begin(edges), end(edges), greater<tuple<int,int,int>>());
	sort(begin(cars), end(cars), greater<pair<int,int>>());
	
	int k = 0;
	for (auto [w,j]: cars) {
		for (; k < m && get<0>(edges[k]) >= w; k++) {
			auto [c,d,i] = edges[k];
			long long diff = max(best[i]-d, 0LL);
			best[i] -= diff, sum -= diff;
		}
		res[j] = sum;
	}
	
	for (long long d: res) {
		if (d < 1e12) cout << d << endl;
		else cout << "impossible" << endl;
	}
}
