#include <iostream>
#include <map>
#include <vector>

using namespace std;

int main()
{
	int n, d;
	cin >> n >> d;
	vector<int> p(n);
	for (auto& x : p)
		cin >> x;
	vector<vector<int>> positions(n + 1);
	for (int i = 0; i < n; i++)
		positions[p[i]].emplace_back(i);
	for (int mex = 0;; mex++) {
		const auto& p = positions[mex];
		for (int i = 0, next = -1e6; i < p.size();) {
			int j = i + 1;
			// find next gap of width d
			while (j < p.size() and p[j - 1] + d >= p[j])
				j++;
			if (next > p[i]) goto fail;
			if (p[j - 1] - p[i] >= d) goto fail;
			next = max(next, min(p[i], p[j-1] - d)) + 2*d;
			i = j;
		}
		cout << mex << endl;
		break;
	fail:;
	}
}
