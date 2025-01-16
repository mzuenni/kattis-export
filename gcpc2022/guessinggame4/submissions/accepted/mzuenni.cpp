#include <bits/stdc++.h>
using namespace std;

#define all(x) begin(x), end(x)
#define sz(x) (ll)(x).size()

using ll = long long;
using ld = long double;

ll prefix[10];

struct sat2 {
	int n;
	vector<int> sol;
	vector<vector<int>> adjlist;

	int counter, sccCounter;
	vector<bool> inStack;
	vector<vector<int>> sccs;
	// idx enthält den Index der SCC pro Knoten.
	vector<int> d, low, idx, s;


	sat2(int vars) : n(vars*2), adjlist(vars*2) {};

	static int var(int d, int i) {
		if(i > 0) return (prefix[d] + i - 1) << 1;
		else return 1^((prefix[d] - i - 1) << 1);
	}

	void addImpl(int v1, int v2) {
		adjlist[v1].push_back(v2);
		adjlist[1^v2].push_back(1^v1);
	}
	void addEquiv(int v1, int v2) {addImpl(v1, v2); addImpl(v2, v1);}
	void addOr(int v1, int v2) {addImpl(1^v1, v2);}
	void addXor(int v1, int v2) {addOr(v1, v2); addOr(1^v1, 1^v2);}
	void addTrue(int v1) {addImpl(1^v1, v1);}
	void addFalse(int v1) {addTrue(1^v1);}
	void addAnd(int v1, int v2) {addTrue(v1); addTrue(v2);}
	void addNand(int v1, int v2) {addOr(1^v1, 1^v2);}

	void visit(int v) {
		d[v] = low[v] = counter++;
		s.push_back(v); inStack[v] = true;

		for (auto u : adjlist[v]) {
			if (d[u] < 0) {
				visit(u);
				low[v] = min(low[v], low[u]);
			} else if (inStack[u]) {
				low[v] = min(low[v], low[u]);
		}}

		if (d[v] == low[v]) {
			sccs.push_back({});
			int u;
			do {
				u = s.back(); s.pop_back(); inStack[u] = false;
				idx[u] = sccCounter;
				sccs[sccCounter].push_back(u);
			} while (u != v);
			sccCounter++;
	}}

	void scc() {
		inStack.assign(sz(adjlist), false);
		d.assign(sz(adjlist), -1);
		low.assign(sz(adjlist), -1);
		idx.assign(sz(adjlist), -1);

		counter = sccCounter = 0;
		for (int i = 0; i < sz(adjlist); i++) {
			if (d[i] < 0) visit(i);
	}}

	bool solvable() {
		scc(); //scc code von oben
		for (int i = 0; i < n; i += 2) {
			if (idx[i] == idx[i + 1]) return false;
		}
		return true;
	}

	void assign() {
		sol.assign(n, -1);
		for (int i = 0; i < sccCounter; i++) {
			if (sol[sccs[i][0]] == -1) {
				for (int v : sccs[i]) {
					sol[v] = 1;
					sol[1^v] = 0;
	}}}}
};

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);
	ll n;
	cin >> n;

	prefix[0] = 0;
	for(int i=1; i<=7; i++){
		cin >> prefix[i];
		prefix[i] += prefix[i-1];
	}

	sat2 sat(prefix[7]);

	for (ll i = 0; i < n; i++) {
		vector<ll> in(7);
		for (ll j = 0; j < 7; j++) {
			ll x;
			cin >> x;
			in[j] = sat2::var(j, x);
			for (ll k = 0; k < j; k++) {
				sat.addNand(in[j], in[k]);
			}
		}
	}
	for (ll i = 5; i < 7; i++) {
		ll x;
		cin >> x;
		sat.addTrue(sat2::var(i, x));
	}
	cout << (sat.solvable() ? "possible" : "impossible") << endl;
}
