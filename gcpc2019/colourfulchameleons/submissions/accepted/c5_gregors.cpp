#include <iostream>
using namespace std;

using ll = long long;
const int MAX_N = 1e5;
ll x[MAX_N];

int main()
{
	int n,t,y; cin >> n >> t >> y;
	t--;
	int rem = -1;
	ll sum = 0;
	for (int i = 0; i < n; ++i)
	{
		cin >> x[i];
		sum += x[i];
		if (i == t)
			continue;
		int r = x[i] % (y+1);
		if (rem == -1)
			rem = r;
		else if (r != rem)
		{
			cout << "impossible" << endl;
			return 0;
		}
	}
	int u = 0;
	for (int i = 0; i < n; ++i)
		if (i != t && x[i] > u)
			u = x[i];
	sum += (ll) u * (y-n+1);
	cout << u << " " << sum << endl;
}
