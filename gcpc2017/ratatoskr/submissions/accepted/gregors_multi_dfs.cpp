// for each node v, root tree at v and compute tree depth
// take minimum of depths
// special cases when one of the ravens stays at its original position
// O(n^2) solution
#include <iostream>
#include <vector>
#include <cstring>
using namespace std;
#define pb push_back
const int MAX_N = 1005;

vector<int> g[MAX_N];
int dfsNum[MAX_N];

int dfs(int cur, int parent, int num)
{
	dfsNum[cur] = num;
	int maxNum = num;
	for (int v : g[cur])
		if (v != parent)
			maxNum = max(maxNum, dfs(v, cur, num+1));
	return maxNum;
}

int squirrelDepth(int n, int s, int r)
{
	memset(dfsNum, -1, n * sizeof(int));
	for (int v : g[r])
	{
		int depth = dfs(r, -1, 0);
		if (dfsNum[s] != -1)
			return depth;
	}
	return -1;
}

int main()
{
	int n, s, r1, r2;
	cin >> n >> s >> r1 >> r2;
	s--, r1--, r2--;
	for (int i = 0; i < n-1; ++i)
	{
		int x,y;
		cin >> x >> y;
		x--, y--;
		g[x].pb(y);
		g[y].pb(x);
	}
	int minDepth = MAX_N + 1;
	for (int i = 0; i < n; ++i)
	{
		memset(dfsNum, -1, n * sizeof(int));
		minDepth = min(minDepth, dfs(i, -1, 1));
	}
	minDepth = min(minDepth, squirrelDepth(n, s, r1));
	minDepth = min(minDepth, squirrelDepth(n, s, r2));
	cout << minDepth << endl;
}
