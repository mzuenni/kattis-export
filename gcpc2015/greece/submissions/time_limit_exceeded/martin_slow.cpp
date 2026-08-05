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

/** Greece 

		Floyd-Warshall to get the transitive hull. -> Time Limit
		TSP DP with and without ticket option to get the min travel time.
**/

#define INF (INT_MAX/2)
int N,P,M,G,T;
int B[20048][20048];
int A[32][32];
vector<int> cities;


int mem[16][1<<16];
int tsp(int pos, int mask)
{
	if(mask == (1<<N)-1) return A[pos][0];
	if(mem[pos][mask] != -1) return mem[pos][mask];
	int erg = INF;
	for(int nxt = 0; nxt < N; nxt++)
	{
		if(nxt == pos || (mask & (1<<nxt)) != 0 || A[pos][nxt] == INF) continue;
		erg = min(erg, A[pos][nxt] + tsp(nxt, mask | (1 << nxt)));		
	}
	mem[pos][mask] = erg;
	return erg;
}

int mem_ticket[16][1<<16][2];
int tsp_ticket(int pos, int mask, bool ticket_used)
{
	if(mask == (1<<N)-1)
	{
		if(ticket_used)	return A[pos][0];
		else return min(A[pos][0], T);
	}
	if(mem_ticket[pos][mask][ticket_used] != -1) return mem_ticket[pos][mask][ticket_used];
	int erg = INF;
	for(int nxt = 0; nxt < N; nxt++)
	{
		if(nxt == pos || (mask & (1<<nxt)) != 0) continue;
		if(A[pos][nxt] != INF) erg = min(erg, A[pos][nxt] + tsp_ticket(nxt, mask | (1 << nxt), ticket_used));
		if(ticket_used == false) erg = min(erg, T + tsp_ticket(nxt, mask | (1 << nxt), true));
	}	
	mem_ticket[pos][mask][ticket_used] = erg;
	return erg;
}

int main()
{  
 	int C;
		cin>>N>>P>>M>>G>>T;		
		cities.clear();
		cities.push_back(0);
		for(int i=0;i<P;i++)
		{
			int p,t;
			cin>>p>>t;		
			if(p != 0) cities.push_back(p);	
			G -= t;			
		}
		for(int i=0;i<N;i++) for(int j=0;j<N;j++) B[i][j] = INF;
		for(int i=0;i<N;i++) B[i][i] = 0;		
		for(int i=0;i<M;i++)
		{
			int s,d,t;
			cin>>s>>d>>t;
			B[s][d] = B[d][s] = min(B[s][d], t);
		}
		for(int k=0;k<N;k++) for(int i=0;i<N;i++) for(int j=0;j<N;j++) B[i][j] = min(B[i][j], B[i][k] + B[k][j]);
		for(int i=0;i<(int)cities.size();i++) for(int j=0;j<(int)cities.size();j++) A[i][j] = B[cities[i]][cities[j]];				
		N = cities.size();
		for(int i=0;i<N;i++) for(int j=0;j<(1<<N);j++) mem[i][j] = mem_ticket[i][j][0] = mem_ticket[i][j][1] = -1;
		int erg = tsp(0, 1);
		if(erg > G)
		{
			erg = tsp_ticket(0, 1, false);
			if(erg <= G) cout << "possible with taxi\n";
			else cout << "impossible\n";
		}
		else cout << "possible without taxi\n";
  return 0;
}


