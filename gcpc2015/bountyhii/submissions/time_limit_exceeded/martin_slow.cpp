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

/*
	Vertex-Disjoint Min Path Cover on DAG
	
	This is intended solution with O(N^4) of wasted steps added.
	O(N^4) calculations should result in a time limit. 
*/

#define MAX_V (2*1000+2)
#define INF (INT_MAX / 2)

int M[MAX_V/2][MAX_V/2];
static volatile int erg = 0;

vector<int> adjList[MAX_V];
int visited[MAX_V];
int match[MAX_V];
int N;

int augment(int v)
{
	if(visited[v] == 1) return 0;
	visited[v] = 1;
	for(int i=0;i<(int)adjList[v].size();i++)
	{
		int u = adjList[v][i];
		if(match[u] == -1 || augment(match[u]) == 1)
		{
			match[u] = v;
			return 1;
		}
	}
	return 0;
}

int mcbm()
{
	int erg = 0;
	for(int j=0;j<MAX_V;j++) match[j] = -1;
	for(int i=0;i<N;i++)
	{
		for(int j=0;j<MAX_V;j++) visited[j] = 0;
		erg += augment(i);
	}
	return erg;
}

int main()
{  
 	cin>>N;
	for(int i=0;i<MAX_V;i++) adjList[i].clear();
	for(int i=0;i<N;i++)
	{
		int K;
		cin>>K;
		for(int j=0;j<K;j++)
		{
			int P;
			cin>>P;
			adjList[i].push_back(P+N);
		}
	}

	/* time wasted */		
	for(int i=0;i<N;i++)for(int j=0;j<N;j++)for(int k=0;k<N;k++)for(int l=0;l<N;l++)
	{
		erg += M[i][j] += M[k][l];
	}
	
	cout << N - mcbm() << "\n";

  return 0;
}


