#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
#define sz(c) ll((c).size())
#define FOR(i,a,b) for (ll i = (a); i < (b); i++)

int main() {
	string z;
	ll n;
	cin >> n;
	
	set<string> d;
	map<string,vector<string>> adj;
	map<string,ll> indeg;
	FOR(i,0,n) {
		string s, t, cmp;
		cin >> s >> cmp >> t;
		if (s == t) {
			cout << "impossible" << endl;
			return 0;
		}
		d.insert(s), d.insert(t);
		if (cmp == ">") swap(s,t);
		adj[s].push_back(t), indeg[t]++;
	}
	queue<string> q;
	for (string s : d) if (!indeg[s]) q.push(s);
	
	while (sz(q)) {
		string s = q.front(); q.pop();
		for (string t : adj[s]) if (!--indeg[t]) q.push(t);
	}
	
	for (string s : d) if (indeg[s]) {
		cout << "impossible" << endl;
		return 0;
	}
	cout << "possible" << endl;
}

