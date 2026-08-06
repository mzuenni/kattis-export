#include <bits/stdc++.h>
using namespace std;

#define fora(i, n) for (int i = 0; i < n; ++i)
#define forb(i, n) for (int i = 1; i<= n; ++i)
#define forc(i, n) for (const auto &i : n)
#define mp make_pair
#define eb emplace_back
#define pb push_back
#define sz(x) (int)(x).size()

using ll = long long;
using ld = long double;
using vi = vector<int>;

vector<vector<long long>> adjList;
vector<long long> dist;

void dfs(long long c, long long pref) {
	for (long long n : adjList[c]) {
		if (n == pref) continue;
		dist[n] = dist[c] + 1;
		dfs(n, c); 
	}
}

long long dfs(long long c) {
	dist = vector<long long>(adjList.size(), -1);
	dist[c] = 0;
	dfs(c, -1);
	long long res = 0;
	for (long long i = 0; i < adjList.size(); i++) {
		if (dist[i] > dist[res]) {
			res = i;
		}
	}
	return res;
}

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);
	long long t;
	cin >> t;
	for (long long i = 0; i < t; i++) {
		long long n;
		cin >> n;
		adjList = vector<vector<long long>>(n);
		for (long long i = 0; i < n - 1; i++) {
			long long a, b;
			cin >> a >> b;
			adjList[a].push_back(b);
			adjList[b].push_back(a);
		}
		long long x = dfs(dfs(0));
		cout << ((dist[x] + 1) / 2) << endl;		
	}
}
