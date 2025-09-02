#include <bits/stdc++.h>
using namespace std;

const int oo = 1e9;

struct flow_network {
	struct edge { int to, cap, cost; };

	int n, s, t;
	vector<vector<int>> adj;
	vector<edge> e;
	
	flow_network(int n, int s, int t): n(n), s(s), t(t), adj(n) { }

	void add_edge(int a, int b, int cap, int cost) {
		adj[a].push_back(e.size());
		e.push_back({b,cap,cost});
		adj[b].push_back(e.size());
		e.push_back({a,0,-cost});
	}

	pair<int,int> mcmf() {
		vector<int> pot(n);
		for (int t = 0; t < n; t++) {
			for (int i = 0; i < n; i++) {
				for (int k: adj[i]) if (e[k].cap) {
					pot[e[k].to] = min(pot[e[k].to],pot[i] + e[k].cost);
				}
			}
		}
		int flow = 0, cost = 0;
		while (true) {
			vector<int> dist(n,oo), pred(n);
			set<pair<int,int>> q;
			dist[s] = 0, q.insert({0,s});
			while (!q.empty()) {
				int i = begin(q)->second;
				q.erase(begin(q));
				for (int k: adj[i]) if (e[k].cap) {
					int j = e[k].to, ndist = dist[i] + e[k].cost + pot[i] - pot[j];
					if (ndist >= dist[j]) continue;
					q.erase({dist[j],j});
					dist[j] = ndist, pred[j] = k;
					q.insert({dist[j],j});
				}
			}
			if (dist[t] == oo) break;

			int cap = oo, cost1 = 0;
			for (int i = t; i != s; i = e[pred[i]^1].to) {
				cap = min(cap,e[pred[i]].cap), cost1 += e[pred[i]].cost;
			}
			flow += cap, cost += cap*cost1;
			for (int i = t; i != s; i = e[pred[i]^1].to) {
				e[pred[i]].cap -= cap, e[pred[i]^1].cap += cap;
			}

			for (int i = 0; i < n; i++) pot[i] += dist[i];
		}
		return {flow,cost};
	}
};

int period(string s) {
	int n = s.size();
	for (int i = 1; i < n; i++) {
		if (n%i == 0 && s.substr(i) == s.substr(0,n-i)) return i;
	}
	return n;
}

#define count asdf
const int S = 251;
int count[2][S];

int main() {
	int n; cin >> n;
	for (int i = 0; i < 2; i++) {
		for (int j = 0; j < n; j++) {
			string s; cin >> s;
			count[i][period(s)]++;
		}
	}
	
	int N = 2*S+2, s = N-2, t = N-1;
	flow_network F(N,s,t);
	
	for (int j = 0; j < S; j++) {
		for (int k = 0; k < S; k++) {
			int cost = (j-k)*(j-k);
			F.add_edge(j,S+k,oo,cost);
		}
	}
	
	for (int j = 0; j < S; j++) {
		F.add_edge(s,j,count[0][j],0);
		F.add_edge(S+j,t,count[1][j],0);
	}

	cout << F.mcmf().second << endl;
}
