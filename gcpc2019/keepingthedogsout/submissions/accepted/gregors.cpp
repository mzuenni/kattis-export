#include <iostream>
#include <vector>
using namespace std;
using ll = long long;

int main()
{
	int n; cin >> n;
	vector<ll> m(n+1);
	ll sum = 0;
	for (int i = 0; i <= n; ++i)
	{
		cin >> m[i];
		sum += m[i] * (1ll << i) * (1ll << i);
	}
	for (ll i = 1; i * i <= sum; ++i)
	{
		if (sum % i != 0) continue;
		bool poss = true;
		ll covered = 0;
		ll j = sum / i;
		for (int k = n; k >= 0 && poss; k--)
		{
			ll z = 1 << k;
			covered += z * z * m[k];
			ll area = (i / z) * z * (j / z) * z;
			if (covered > area)
				poss = false;
		}
		if (poss)
		{
			cout << i << " " << sum / i << endl;
			return 0;
		}
	}
	cout << "impossible" << endl;
}
