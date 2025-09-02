#include <bits/stdc++.h>
using namespace std;

map<string,vector<string>> adj;

bool reach(string s, string t) {
	if (s == t) return true;
	for (string r: adj[s])
		if (reach(r,t)) return true;
	return false;
}

int main() {
	int n, m; cin >> n >> m;
	string a, b, foo, res;

	while (n--) {
		cin >> a >> foo >> foo >> foo >> b;
		adj[a].push_back(b);
	}
	
	while (m--) {
		cin >> a >> foo >> foo >> foo >> b;
		if (a == b) res = "Alternative Fact";
		else if (reach(a,b)) res = "Fact";
		else if (reach(b,a)) res = "Alternative Fact";
		else res = "Pants On Fire";
		cout << res << endl;
	}
}
