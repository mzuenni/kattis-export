#include <iostream>
#include <vector>
#include <cstring>
using namespace std;
#define pb push_back

const int MAX_N = 1005;

vector<int> g[MAX_N];
bool visited[MAX_N];

int subtreeDepth(int cur)
{
	visited[cur] = true;
	int maxDepth = 0;
	for (int neigh : g[cur])
		if (!visited[neigh])
			maxDepth = max(maxDepth, subtreeDepth(neigh));
	return 1 + maxDepth;
}

int squirrelDepth(int squirrel, int raven)
{
	memset(visited, false, MAX_N * sizeof(bool));
	visited[raven] = true;
	for (int neigh : g[raven])
	{
		int depth = subtreeDepth(neigh);
		if (visited[squirrel])
			return depth;
	}
	return -1;
}

int main()
{
	int n, r, h, m;
	cin >> n >> r >> h >> m;
	r--, h--, m--;

	for (int i = 0; i < n-1; ++i)
	{
		int x,y;
		cin >> x >> y;
		x--, y--;
		g[x].pb(y);
		g[y].pb(x);
	}
	cout << min(squirrelDepth(r,h), squirrelDepth(r,m)) << endl;
}
