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
using namespace std;
#define db(a) (cout << (#a) << " = " << (a) << endl)
typedef long long ll;

ll N, M;
const size_t NUM = 256;
bool G[NUM][NUM];
unordered_map<string, ll> names;

int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);
	cin>>N>>M;
	ll r = 0;
	for(size_t i=0;i<NUM;i++) for(size_t j=0;j<NUM;j++) G[i][j] = false;
	for(ll i=0;i<N;i++) 
	{
		string a;
		string b;
		cin>>a>>b>>b>>b>>b;
		if(names.count(a) == 0) names[a] = r++;
		if(names.count(b) == 0) names[b] = r++;
		G[names[b]][names[a]] = true;		
	}

	for(size_t k=0;k<NUM;k++) for(size_t i=0;i<NUM;i++) for(size_t j=0;j<NUM;j++) if(G[i][k] && G[k][j]) G[i][j] = true;

	for(ll i=0;i<M;i++)
	{
		string a, b;
		cin>>a>>b>>b>>b>>b;
		if(names.count(a) == 0 || names.count(b) == 0) cout << "Pants on Fire\n";
		else if(G[names[b]][names[a]]) cout << "Fact\n";
		else if(G[names[a]][names[b]]) cout << "Alternative Fact\n";
		else cout << "Pants on Fire\n";
	}

	return 0;
}

