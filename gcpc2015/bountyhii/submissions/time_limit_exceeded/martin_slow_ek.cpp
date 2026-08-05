#include <iostream>
#include <algorithm>
#include <string>
#include <cmath>
#include <vector>
#include <sstream>
#include <stack>
#include <queue>
#include <map>
#include <climits>
#include <cstdio>
#include <set>
#include <bitset>
using namespace std;
#define db(a) (cout << (#a) << " = " << (a) << endl)
typedef long long ll;

/** Vertex-Disjoint Min Path Cover on DAG
		
		Slow max flow solution. Runs in O(V^3 * E).
**/

#define MAX_V (2*1000+2)
#define INF (INT_MAX / 2)

/* Edmonds-Karp */
int source, target, f;
int res[MAX_V][MAX_V];
int p[MAX_V];
 
void augment(int v, int minEdge)
{
	if(v == source)
	{
		f = minEdge;
		return; 
	}
	if(p[v] != -1)
	{
		augment(p[v], min(minEdge, res[p[v]][v]));
		res[p[v]][v] -= f;
		res[v][p[v]] += f;
	}
}

int maxFlow() // first init res, s and t
{
	int mf = 0;
	while(true)
	{
		f = 0;
		bitset<MAX_V> vis;
		vis[source] = true;
		queue<int> q;
		q.push(source);
		for(int i=0;i<MAX_V;i++) p[i] = -1;
		while(!q.empty())
		{
			int u = q.front();
			q.pop();
			if(u == target) break;
			// Slow version without adjacency list
			for(int v = 0;v<MAX_V;v++)
			{
				if(res[u][v] > 0 && !vis[v])
				{
					vis[v] = true;
					q.push(v);
					p[v] = u;
				}
			}
		}	
		augment(target, INF);
		if(f == 0) break;
		mf += f;
	}
	return mf;
}



int main()
{  
	int N;
 	cin>>N;
	for(int i=0;i<MAX_V;i++) for(int j=0;j<MAX_V;j++) res[i][j] = 0;
	for(int i=0;i<N;i++)
	{
		int K;
		cin>>K;
		for(int j=0;j<K;j++)
		{
			int P;
			cin>>P;
			res[i][P+N] = 1;		
		}
	}
	source = 2*N;
	target = 2*N+1;
	for(int i=0;i<N;i++)
	{
		res[source][i] = 1;
	}
	for(int i=0;i<N;i++)
	{
		res[i+N][target] = 1;
	}
	cout << N - maxFlow() << "\n";

  return 0;
}

