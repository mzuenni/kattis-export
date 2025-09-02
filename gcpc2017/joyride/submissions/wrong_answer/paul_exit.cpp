#include <bits/stdc++.h>
using namespace std;

#define time asdf

const int N = 1001, oo = 0x3f3f3f3f;
vector<int> adj[N];
int time[N], cost[N];
int dp[N][N];

int main() {
	int max_time, n, m;
	cin >> max_time >> n >> m;
	
	while (m--) {
		int a, b; cin >> a >> b;
		a--, b--;
		adj[a].push_back(b);
		adj[b].push_back(a);
	}
	
	for (int i = 1; i < n; i++) cin >> time[i] >> cost[i];
	
	memset(dp,0x3f,sizeof dp);

	dp[0][0] = 0;

	for (int t = 0; t <= max_time; t++)
		for (int i = 0; i < n; i++) 
			for (int j: adj[i])
				if (t + time[j] <= max_time)
					dp[t+time[j]][j] = min(dp[t+time[j]][j], dp[t][i]+cost[j]);
	
	int res = dp[max_time][0];

	if (res < oo) cout << res << endl;
	else cout << "It is a trap." << endl;
}
