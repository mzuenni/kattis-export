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

int H,W,N;
vector<string> names,names2;

int G[32][32];
pair<int,int> DP[21][1<<21];
int Path[21][1<<21];

pair<int,int> add(const int d, const pair<int,int> p, int i)
{
	if(p.second + d <= W) return {p.first, p.second+d};
	return {p.first+1, names[i].size()};
}

pair<int,int> tsp(int pos, int mask)
{
	if(mask == (1<<(N+1))-1) return {0, names[pos].size()};
	if(DP[pos][mask] != pair<int,int>(-1, -1)) return DP[pos][mask];
	pair<int,int> ret = {INT_MAX/2, INT_MAX/2};
	for(int i=0;i<N;i++)
	{
		if(i==pos || (mask & (1<<i))!=0) continue;		
		auto x = (add(G[i][pos], tsp(i, mask | (1<<i)), pos));
		if(ret > x)
		{
			ret = x;
			Path[pos][mask] = i;
		}
	}
	DP[pos][mask] = ret;
	return ret;
}

int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);
	cin>>H>>W>>N;
	for(int i=0;i<N;i++) 
	{
		string in;
		cin>>in;
		if((int)in.size()>W)
		{
			cout << "impossible\n";
			return 0;
		}
		names2.push_back(in);
	}
	for(const auto &in: names2) 
	{
		bool insert = true;
		for(const auto& s : names2) if(s != in && s.find(in) != string::npos) insert = false;
		if(insert) names.push_back(in);
	}
	N = (int)names.size();
	for(int i=0;i<N;i++) for(int j=0;j<N;j++)
	{
		G[i][j] = names[j].size();
		for(int k=0;k<(int)names[i].size();k++)
		{
			auto a = names[i].substr(k);
			auto b = names[j].substr(0, names[i].size() - k);
			if(a==b)
			{
				G[i][j] = names[j].size() - b.size();
				break;
			}
		}
	}
	for(int i=0;i<N;i++) G[i][N] = G[N][i] = 0;
	
	for(int j=0;j<21;j++) for(int i=0;i<1<<21;i++) DP[j][i] = {-1,-1};
	for(int j=0;j<21;j++) for(int i=0;i<1<<21;i++) Path[j][i] = -1;	
	auto erg = tsp(N, 1<<N);
	
	if(erg.first >= H) cout << "impossible\n";		
	else
	{
		int i=Path[N][1<<N];
		int mask=(1<<N) | (1<<i);
		vector<int> p;
		while(i!=-1)
		{
			p.push_back(i);
			i=Path[i][mask];
			mask |= 1<<i;
		}
		reverse(p.begin(), p.end());
		
		pair<int,int> g = {0, 0};
		int last=-1;
		for(auto i : p)
		{			
			string s = names[i];			
			if(last!=-1) s = s.substr(s.size()-G[last][i]);
			if(g.second + (int)s.size() > W)
			{
				for(int i=g.second;i<W;i++) cout << "X";
				cout << "\n";
				cout<<names[i];
				g.second = names[i].size();
				g.first++;
				last=i;
			}
			else
			{
				cout<<s;
				g.second += s.size();
				last=i;
			}
		}		
		for(int i=g.second;i<W;i++) cout << "X";
		cout << "\n";
		while(g.first+1<H)
		{
			g.first++;
			for(int i=0;i<W;i++) cout << "X";
			cout << "\n";
		}
	}

	return 0;
}

