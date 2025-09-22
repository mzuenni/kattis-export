#include <iostream>
#include <vector>
#include <utility>
#include <map>
using namespace std;

const int MAX_N = 1001;
map<char,int> plan[MAX_N];
map<char,int> level[MAX_N];
map<string,int> artifact;

int exploreLevel(int n)
{
    string a,s; cin >> a >> s;
    if (artifact.count(a)) 
    	return artifact[a];
    artifact[a] = artifact.size();
    if (artifact.size() > n)
		return -1;
    for (char t : s) 
    {
        cout << "W " << t << endl << flush;
        int dst = exploreLevel(n);
        level[artifact[a]].emplace(t,dst);
        cout << "W " << t << endl << flush;
        string a2,s2; cin >> a2 >> s2;
    }
    return artifact[a];
}

bool verifyMapping(int pnode, int lnode, vector<char> &visited)
{
	if (visited[pnode])
		return true;
	visited[pnode] = true;
	if (plan[pnode].size() != level[lnode].size())
		return false;
	for (auto &p : plan[pnode])
	{
		char t = p.first;
		int pdst = p.second;
		if (!level[lnode].count(t))
			return false;
		int ldst = level[lnode].at(t);
		if (!verifyMapping(pdst,ldst,visited))
			return false;
	}
	return true;
}

int main()
{
	int n; cin >> n;
	for (int i = 0; i < n; ++i)
	{
		int k; cin >> k;
		for (int j = 0; j < k; ++j)
		{
			char t; int m; cin >> t >> m;
			plan[i].emplace(t,--m);
		}
	}
	int lnode = exploreLevel(n);
	if (artifact.size() != n)
	{
		cout << "R no" << endl << flush;
		exit(0);
	}
	int location = -1;
	for (int pnode = 0; pnode < n; ++pnode)
	{
		vector<char> visited(n,false);
		if (verifyMapping(pnode,lnode,visited))
		{
			if (location == -1)
				location = pnode;
			else
			{
				location = -2;
				break;
			}
		}
	}
	if (location == -1)
		cout << "R no" << endl << flush;
	else if (location == -2)
		cout << "R ambiguous" << endl << flush;
	else
		cout << "R " << location+1 << endl << flush;
}
