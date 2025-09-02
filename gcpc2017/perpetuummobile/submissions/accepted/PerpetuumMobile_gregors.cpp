#include <iostream>
#include <vector>
#include <cmath>
#include <limits>
using namespace std;

bool fw(int n, vector<vector<double>> &dist)
{
	for (int k = 0; k < n; ++k)
	{
		for (int i = 0; i < n; ++i)
		{
			for (int j = 0; j < n; ++j)
			{
				dist[i][j] = min(dist[i][j], dist[i][k] + dist[k][j]);
				if (i == j && dist[i][j] < 0)
					return true;
			}
		}
	}
	return false;
}

int main()
{
	int n,m;
	cin >> n >> m;
	vector<vector<double>> dist(n, vector<double>(n,99999));

	for (int i = 0; i < m; ++i)
	{
		int a,b;
		double c;
		cin >> a >> b >> c;
		dist[a-1][b-1] = min(dist[a-1][b-1], -log(c));
	}

	if (fw(n, dist))
		cout << "inadmissible" << endl;
	else
		cout << "admissible" << endl;
}
