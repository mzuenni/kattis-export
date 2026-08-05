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
		
		Greedy solution. Wrong Answer.
**/

#define MAX_V (2*1000+2)
#define INF (INT_MAX / 2)

vector<int> adjList[MAX_V];
vector<int> invAdjList[MAX_V];
int visited[MAX_V];

int main()
{  
	int N;
		cin>>N;
	for(int i=0;i<MAX_V;i++)
	{
		adjList[i].clear();
		invAdjList[i].clear();			
		visited[i] = 0;
	}
	for(int i=0;i<N;i++)
	{
		int K;
		cin>>K;
		for(int j=0;j<K;j++)
		{
			int P;
			cin>>P;
			adjList[i].push_back(P);
			invAdjList[P].push_back(i);
		}
	}
		
	int erg = 0;
	for(int i=0;i<N;i++)
	{
		if(visited[i] > 0) continue;
		int r = i;
		bool done = false;
		while(invAdjList[r].size() > 0 && !done)
		{
			if(visited[r] > 0) break;
			done = true;
			for(int j=0;j<(int)invAdjList[r].size();j++) 
			{
				if(visited[invAdjList[r][j]] > 0) continue;
				done = false;
				r = invAdjList[r][j];					
				break;
			}								
		}
		
		done = false;
		while(adjList[r].size() > 0 && !done)
		{
			visited[r] = 1;
			done = true;
			for(int j=0;j<(int)adjList[r].size();j++) 
			{
				if(visited[adjList[r][j]] > 0) continue;
				r = adjList[r][j];
				done = false;
				break;
			}
		}
		visited[r] = 1;
		
		erg++;			
	}
		
	cout << erg << "\n";
	
  return 0;
}

