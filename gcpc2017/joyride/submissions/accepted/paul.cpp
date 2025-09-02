#include <bits/stdc++.h>
using namespace std;

#define time asdf

const int N = 1001, oo = 0x3f3f3f3f;
vector<int> adj[N];
int time[N], cost[N];
int dp[N][N];

int main() {
	int max_time, n, m, T;
	cin >> max_time >> n >> m >> T;
	
	while (m--) {
		int a, b; cin >> a >> b;
		a--, b--;
		adj[a].push_back(b);
		adj[b].push_back(a);
	}
	
	for (int i = 0; i < n; i++) cin >> time[i] >> cost[i];
	
	memset(dp,0x3f,sizeof dp);

	dp[0][0] = 0;
	if (time[0] > max_time){
		cout << "It is a trap." << endl;
		return 0;
	}
	max_time -= time[0];

	for (int t = 0; t <= max_time; t++)
		for (int i = 0; i < n; i++) {
			if (t + time[i] <= max_time)
				dp[t+time[i]][i] = min(dp[t+time[i]][i], dp[t][i]+cost[i]);
			for (int j: adj[i])
				if (t + time[j] + T <= max_time)
					dp[t+time[j]+T][j] = min(dp[t+time[j]+T][j], dp[t][i]+cost[j]);
	}
	
	int res = dp[max_time][0] + cost[0];

	if (res < oo) cout << res << endl;
	else cout << "It is a trap." << endl;
}
