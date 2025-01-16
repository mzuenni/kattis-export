#include <bits/stdc++.h>
using namespace std;

struct scc {
	int n, C = 0, T = 0, top = -1;
	vector<int> comp, t, st;
	vector<vector<int>> adj;

	int dfs(int i) {
		int tmin = t[i] = T++;
		st[++top] = i;
		for (int j: adj[i]) if (comp[j] == -1) {
			tmin = min(tmin, t[j] == -1 ? dfs(j) : t[j]);
		}
		if (tmin == t[i]) {
			while (st[top] != i) comp[st[top--]] = C;
			comp[st[top--]] = C++;
		}
		return tmin;
	}

	scc(vector<vector<int>> adj): n(size(adj)), comp(n,-1), t(n,-1), st(n), adj(adj) {
		for (int i = 0; i < n; i++) if (t[i] == -1) dfs(i);
	}
};

struct sat2 {
	int n;
	vector<vector<int>> adj;
	vector<int> val;

	sat2(int n): n(n), adj(2*n), val(n) { }

	void add(int a, int b) { adj[n+a].push_back(n+b), adj[n+~b].push_back(n+~a); }

	void Or   (int a, int b) { add(~a,b); }
	void True (int a)        { Or(a,a); }
	void False(int a)        { True(~a); }
	void Same (int a, int b) { add(a,b), add(b,a); }
	void Xor  (int a, int b) { Same(a,~b); }

	void AtMostOne(vector<int> as) {
		for (int a: as) for (int b: as) if (a < b) Or(~a,~b);
	}

	bool check() {
		scc S(adj);
		for (int i = 0; i < n; i++) {
			if (S.comp[n+~i] == S.comp[n+i]) return false;
			val[i] = S.comp[n+~i] > S.comp[n+i];
		}
		return true;
	}
};

int main() {
	int n; cin >> n;

	array<int,7> g;
	for (int &x: g) cin >> x;

	array<int,8> s = {};
	partial_sum(begin(g), end(g), begin(s)+1);

	vector<vector<int>> picks(n+1, vector<int>(7));
	picks[n].resize(2);
	for (auto &v: picks) {
		int k = size(v);
		for (int i = 0; i < k; i++) {
			int a; cin >> a;
			int x = s[7-k+i] + abs(a) - 1;
			v[i] = a > 0 ? x : ~x;
		}
	}

	sat2 S(s[7]);
	for (int i = 0; i < n; i++) {
		S.AtMostOne(picks[i]);
	}
	for (int k: picks[n]) S.True(k);
	
	cout << (S.check() ? "possible" : "impossible") << '\n';
}
