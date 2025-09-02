#include <iostream>
#include <set>
#include <functional>
#include <vector>
#include <algorithm>
#include <numeric>
using namespace std;

int main()
{
	int w,p; cin >> w >> p;
	vector<int> bribes(w,0);
	for (int i = 0; i < w; ++i)
	{
		int v0; cin >> v0;
		multiset<int,greater<int>> votes;
		for (int j = 1; j < p; ++j)
		{
			int y; cin >> y;
			votes.insert(y);
		}
		while (*votes.begin() >= v0)
		{
			votes.insert(*votes.begin()-1);
			votes.erase(votes.begin());
			bribes[i]++;
			v0++;
		}
	}
	sort(bribes.begin(),bribes.end());
	cout << accumulate(bribes.begin(),bribes.begin()+w/2+1,0) << endl;
}
