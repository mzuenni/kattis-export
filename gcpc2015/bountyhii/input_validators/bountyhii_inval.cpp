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
using namespace std;
#define db(a) (cout << (#a) << " = " << (a) << endl)
typedef long long ll;

/** Input Validator for Bounty Hunter II

		Given graph must be a DAG.
**/

#define CHECK(X) do {\
	if(!(X)) { \
		cout << (#X) << " failed\n"; \
		return 1; } \
	} while(false)

#define FAIL(X) do {\
		cout << (X) << "\n"; \
		return 1; \
	} while(false)

#define MAX_N (1000)

vector<int> adjList[MAX_N];
int vis[MAX_N];

bool dfs(int v)
{
	if(vis[v] == 1) return false;
	if(vis[v] == 0)
	{
		vis[v] = 1;
		for(int i=0;i<(int)adjList[v].size();i++) if(!dfs(adjList[v][i])) return false;
		vis[v] = 2;
	}
	return true;
}

int main()
{
  int N;
  cin>>N;
	CHECK(cin.good() && N>0 && N<=MAX_N);
	for(int i=0;i<MAX_N;i++) adjList[i].clear();
	for(int i=0;i<N;i++)
	{
		int K;
		cin>>K;
		CHECK(cin.good() && K>=0 && K<N);
		for(int j=0;j<K;j++)
		{
			int P;
			cin>>P;
			CHECK(cin.good() && P>=0 && P<N);
			adjList[i].push_back(P);
		}
	}

	// Cycle test.
	for(int i=0;i<N;i++) vis[i] = 0;
	for(int i=0;i<N;i++)
	{
		if(vis[i] != 0) continue;
		CHECK(dfs(i));
	}

  char c;
  while(cin.get(c)) CHECK(c == '\n');
  CHECK(cin.eof());
  return 42;
}
