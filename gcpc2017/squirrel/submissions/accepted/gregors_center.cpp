// Case 1: one of the ravens stays at its original position in the beginning
//		   -> compute depth of subtree with squirrel inside
// Case 2: one of the ravens moves to the center of graph
//		   -> compute deepest subtree rooted at center of graph
// O(n) solution
#include <iostream>
#include <vector>
#include <cstring>
#include <cmath>
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

int diameter(int n)
{
	int maxNum = dfs(0, -1, 0);
	int deepest;
	for (int i = 0; i < n; ++i)
		if (dfsNum[i] == maxNum)
			deepest = i;
	int diam = dfs(deepest, -1, 0);
	return diam;
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
	int a = squirrelDepth(n, s, r1);
	int b = squirrelDepth(n, s, r2);
	int c = ceil(diameter(n)/2.0) + 1;
	cout << min(a,min(b,c)) << endl;
}
