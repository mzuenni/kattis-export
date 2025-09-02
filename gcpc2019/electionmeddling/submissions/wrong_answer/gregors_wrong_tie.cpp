#include <iostream>
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
		for (int j = 1; j < p; ++j)
		{
			int x; cin >> x;
			if (v0 < x)
			{
				int c = (x-v0+1)/2;
				v0 += c;
				bribes[i] += c;
			}
		}
	}
	sort(bribes.begin(),bribes.end());
	cout << accumulate(bribes.begin(),bribes.begin()+w/2+1,0) << endl;
}
