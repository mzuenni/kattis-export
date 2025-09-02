#include <iostream>
#include <vector>
#include <limits>
using namespace std;

const int MAX_N = 1001;
vector<int> g[MAX_N];
int times[MAX_N];
int prices[MAX_N];
int dp[MAX_N][MAX_N]; // time, location

int main()
{
	int x, n, m, t;
	cin >> x >> n >> m >> t;
	for (int i = 0; i < m; ++i)
	{
		int a,b;
		cin >> a >> b;
		a--, b--;
		g[a].push_back(b);
		g[b].push_back(a);
	}
	for (int i = 0; i < n; ++i)
		cin >> times[i] >> prices[i];
	for (int i = 0; i <= x; ++i)
		for (int j = 0; j < n; ++j)
			dp[i][j] = numeric_limits<int>::max();
	if (times[0] > x){
		cout << "It is a trap." << endl;
		return 0;
	}
	x-=times[0];

	dp[0][0] = 0;
	for (int i = 1; i <= x; ++i)
	{
		for (int j = 0; j < n; ++j)
		{
			if (i < times[j])
				continue;
			// stay at same ride
			dp[i][j] = min(dp[i][j], dp[i-times[j]][j]);
			if (i >= times[j] + t) {
				// come from another ride
				for (int prev : g[j])
					dp[i][j] = min(dp[i][j], dp[i-times[j]-t][prev]);
			}
			if (dp[i][j] != numeric_limits<int>::max())
				dp[i][j] += prices[j];
		}
	}
	if (dp[x][0] == numeric_limits<int>::max())
		cout << "It is a trap." << endl;
	else
		cout << dp[x][0] + prices[0] << endl;
}
