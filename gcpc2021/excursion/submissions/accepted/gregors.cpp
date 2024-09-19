#include <iostream>
#include <vector>
#include <algorithm>
#include <utility>
#include <tuple>
using namespace std;

int main()
{
	int n,m; cin >> n >> m;
	vector<tuple<int,int,int>> edges;
	for (int i = 0; i < m; ++i)
	{
		int j,d,t; cin >> j >> d >> t;
		edges.emplace_back(t,d,j);
	}
	sort(edges.begin(),edges.end());
	reverse(edges.begin(),edges.end());
	int q; cin >> q;
	vector<pair<int,int>> cars;
	for (int i = 0; i < q; ++i)
	{
		int g; cin >> g;
		cars.emplace_back(g,i);
	}
	sort(cars.begin(),cars.end());
	reverse(cars.begin(),cars.end());
	vector<int> carDist(q,-1);
	vector<int> dist(n,-1);
	int procEdge = 0;
	int totalDist = 0;
	int unconnected = n-1;
	for (auto &[carWeight,carIdx] : cars)
	{
		while (procEdge < edges.size() && carWeight <= get<0>(edges[procEdge]))
		{
			int d = get<1>(edges[procEdge]);
			int j = get<2>(edges[procEdge]);
			if (dist[j] == -1)
			{
				unconnected--;
				dist[j] = d;
				totalDist += d;
			}
			else if (d < dist[j])
			{
				totalDist = totalDist - dist[j] + d;
				dist[j] = d;
			}
			procEdge++;
		}
		if (unconnected == 0) carDist[carIdx] = totalDist;
	}
	for (int i = 0; i < q; ++i)
	{
		if (carDist[i] == -1) cout << "impossible" << endl;
		else cout << carDist[i] << endl;
	}
}
