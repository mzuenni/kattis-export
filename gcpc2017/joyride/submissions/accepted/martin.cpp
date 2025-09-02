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
#include <array>
#include <unordered_map>
#include <unordered_set>
#include <iomanip>
#include <functional>
#include <random>
using namespace std;
#define db(a) (cout << (#a) << " = " << (a) << endl)
typedef long long ll;

int X;
int N,M,PT;
vector<int> G[1024];
int T[1024];
int P[1024];
int erg;

int DP[1024][1024];

void foo(int i, int time, int money)
{
	time += T[i];
	money += P[i];
	if(time > X) return;
	if(DP[i][time] <= money) return;
	DP[i][time] = money;
	if(i == 0 && time == X) erg = min(erg, money);
	for(const auto& n : G[i]) foo(n, time + PT, money);
	// stay here
	foo(i, time, money);
}

int main()
{
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
	cin>>X>>N>>M>>PT;
	for(int i=0;i<M;i++)
	{
		int a,b;
		cin>>a>>b;
		a--, b--;
		G[a].push_back(b);
		G[b].push_back(a);
	}
	for(int i=0;i<N;i++) cin>>T[i]>>P[i];
	erg = INT_MAX;
	for(int i=0;i<1024;i++)for(int j=0;j<1024;j++) DP[i][j] = INT_MAX;
	foo(0,0,0);
	if(erg < INT_MAX) cout << erg << "\n";
	else cout << "It is a trap.\n";
  return 0;
}

