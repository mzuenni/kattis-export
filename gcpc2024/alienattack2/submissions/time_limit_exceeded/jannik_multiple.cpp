#pragma GCC optimize("Ofast")

#include <iostream>
#include <unordered_set>
#include <vector>

using namespace std;

vector<int> adj[200'000];

int main() {
	cin.tie(nullptr);
	int n, m;
	cin >> n >> m;
	while (m-- > 0) {
		int i, j;
		cin >> i >> j; i--, j--;
		adj[i].push_back(j), adj[j].push_back(i);
	}
	int res = 0;
	for (int i = 0; i < n; i++) {
		vector<int> st = {i};
		unordered_set<int> done = {i};
		for (int i = 0; i < st.size(); i++) {
			for (int k : adj[st[i]])
				if (done.emplace(k).second)
					st.emplace_back(k);
		}
		res = max<int>(res, st.size());
	}
	cout << res << '\n';
}
