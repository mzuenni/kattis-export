// Solve flow with dinic.
// Naive implementation: try out tripling every socket and compute
// new max flow for each setting.

#include <iostream>
#include <vector>
#include <limits>
#include <cstring>
#include <algorithm>
using namespace std;
const int MAX_NODES = 20170;

int numNodes = MAX_NODES;
int dist[MAX_NODES], q[MAX_NODES], visited[MAX_NODES];

struct Edge {int to, rev, f, cap;};
vector<vector<Edge>> g(MAX_NODES);

void addEdge(int s, int t, int cap)
{
	Edge a = {t, (int) g[t].size(), 0, cap};
	Edge b = {s, (int) g[s].size(), 0, 0};
	g[s].push_back(a);
	g[t].push_back(b);
}

bool dinic_bfs(int src, int dest) 
{
	memset(dist, -1, numNodes * sizeof(*dist));
	dist[src] = 0;
	int qSize = 0;
	q[qSize++] = src;
	for (int idx = 0; idx < qSize; ++idx) 
	{
		int u = q[idx];
		for (int j = 0; j < (int) g[u].size(); ++j) 
		{
			Edge &e = g[u][j];
			int v = e.to;
			if (dist[v] < 0 && e.f < e.cap) 
			{
				dist[v] = dist[u] + 1;
				q[qSize++] = v;
			}
		}
	}
	return dist[dest] >= 0;
}

int dinic_dfs(int u, int f, int dest) 
{
	if (u == dest)
		return f;
	for (int &i = visited[u]; i < (int) g[u].size(); ++i) 
	{
		Edge &e = g[u][i];
		if (e.f >= e.cap) 
			continue;
		int v = e.to;
		if (dist[v] == dist[u] + 1) 
		{
			int df = dinic_dfs(v, min(f, e.cap - e.f), dest);
			if (df > 0) 
			{
				e.f += df;
				g[v][e.rev].f -= df;
				return df;
			}
		}
	}
	return 0;
}

int maxFlow(int src, int dest) 
{
	int result = 0;
	while (dinic_bfs(src, dest)) 
	{
		memset(visited, 0, numNodes * sizeof(*visited));
		while (int delta = dinic_dfs(src, numeric_limits<int>::max(), dest))
	  		result += delta;
	}
	return result;
}


int main() 
{
	int m, n, k;
    cin >> m >> n >> k;
    const int SRC = 0;
	const int SINK = m+n+1;
    for (int i = 1; i <= m; ++i)
    	addEdge(SRC, i, 1);
    for (int i = m+1; i <= m+n; ++i)
    	addEdge(i, SINK, 1);
    for (int i = 0; i < k; ++i)
    {
    	int x,y;
    	cin >> x >> y;
    	addEdge(x, y+m, 1);    	
    }
    int s1 = SINK+1;
    int s2 = SINK+2;
    addEdge(SRC, s1, 1);
    addEdge(SRC, s2, 1);
    vector<vector<Edge>> orig_g = g;
    int res = 0;
    // iterate over all the sockets, triple each one of them
    for (int i = 1; i <= m; ++i)
    {
    	for (int j = 0; j < g[i].size(); ++j)
    	{
    		int to = g[i][j].to;
    		// skip residual edges that lead back to source
    		if ((m+1 <= to) && (to <= m+n))
    		{
    			addEdge(s1, to, 1);
    			addEdge(s2, to, 1);
    		}
    	}
    	res = max(res,maxFlow(SRC,SINK));
    	g = orig_g;
    }
    cout << res << endl;
}


