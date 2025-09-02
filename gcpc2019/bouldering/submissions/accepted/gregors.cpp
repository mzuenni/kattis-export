#include <iostream>
#include <vector>
#include <utility>
#include <queue>
#include <cmath>
#include <iomanip>
using namespace std;
const double INF = 1e12;
const int MAX_S = 25*25*9;

struct Hold 
{
	int id,x,y,c;
	vector<int> reachable;
	Hold(int x, int y, int c) : x(x),y(y),c(c) {}
};

double dist(Hold &g1, Hold &g2) 
{
	return sqrt((g1.x - g2.x) * (g1.x - g2.x) + (g1.y - g2.y) * (g1.y - g2.y));
}

int main()
{
	int h,w,r,s; cin >> h >> w >> r >> s;
	s = min(s,MAX_S);
	vector<Hold> holds;
	for (int i = 0; i < h; ++i)
	{
		for (int j = 0; j < w; ++j)
		{
			char c; cin >> c;
			if (c != '.')
				holds.emplace_back(j,h-1-i,c-'0');
		}
	}
	for (int i = 0; i < holds.size(); ++i)
	{
		for (int j = i+1; j < holds.size(); ++j)
		{
			if (dist(holds[i],holds[j]) <= r)
			{
				holds[i].reachable.push_back(j);
				holds[j].reachable.push_back(i);
			}
		}
	}
	vector<vector<double>> dp(holds.size(), vector<double>(s+1,INF));
	queue<pair<int,int>> q;
	int a = holds.size()-1;
	int z = s - holds[a].c;
	if (z >= 0)
	{
		dp[a][z] = 0;
		q.push({a,z});
	}
	while (!q.empty())
	{
		int cur = q.front().first;
		int stam = q.front().second;
		q.pop();
		for (int neigh : holds[cur].reachable)
		{
			if (holds[neigh].c > stam) continue;
			int z = stam - holds[neigh].c;
			if (z >= 0 && dp[cur][stam] + dist(holds[cur],holds[neigh]) < dp[neigh][z])
			{
				dp[neigh][z] = dp[cur][stam] + dist(holds[cur],holds[neigh]);
				q.push({neigh,z});
			}
		}
	}
	double best = INF;
	for (int i = 0; i <= s; ++i)
		best = min(best,dp[0][i]);
	if (best != INF) cout << fixed << setprecision(10) << best << endl;
	else cout << "impossible" << endl;
}
