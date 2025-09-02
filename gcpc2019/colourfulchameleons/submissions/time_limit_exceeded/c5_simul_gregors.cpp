#include <iostream>
#include <algorithm>
using namespace std;

using ll = long long;
const int MAX_N = 1e5;
ll x[MAX_N];

void print(int n)
{
	for (int i = 0; i < n; ++i)
		cout << x[i] << " ";
	cout << endl;
}

void cultivate(int n, int y, int z)
{
	for (int i = 0; i < n; ++i)
		x[i]--;
	x[z] += y+1;
	//print(n);
}

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
	int steps = 0;
	while (true)
	{
		int l = min_element(x,x+n) - x;
		x[t] = -x[t];
		int u = max_element(x,x+n) - x;
		x[t] = -x[t];
		if (x[u] == x[l])
		{
			steps += x[u];
			while (x[u] > 0)
				cultivate(n,y,t);
			break;
		}
		else
		{
			steps++;
			cultivate(n,y,l);
		}
	}
	sum += (ll) steps * (y-n+1);
	cout << steps << " " << sum << endl;
}
