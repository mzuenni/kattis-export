#include <iostream>
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
	vector<bool> done(n);
	int res = 0;
	for (int i = 0; i < n; i++) {
		if (done[i]) continue;
		vector<int> st = {i};
		for (int i = 0; i < st.size(); i++) {
			done[st[i]] = true;
			for (int k : adj[st[i]])
				if (not done[k])
					st.emplace_back(k);
		}
		res = max<int>(res, st.size());
	}
	cout << res << '\n';
}
