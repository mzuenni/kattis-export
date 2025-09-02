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
		vector<int> v(p);
		for (int i = 0; i < p; ++i)
			cin >> v[i];
		int low = 0;
		int high = std::accumulate(v.begin()+1,v.end(),0);
		while (low <= high)
		{
			int mid = (low + high) / 2;
			int needed = 0;
			for (int i = 1; i < p; ++i)
				if (v[0] + mid <= v[i])
					needed += v[i] - v[0] - mid + 1;
			if (mid < needed) 
				low = mid + 1;
			else 
				high = mid - 1;
		}
		bribes[i] = low;
	}
	sort(bribes.begin(),bribes.end());
	cout << accumulate(bribes.begin(),bribes.begin()+w/2+1,0) << endl;
}
