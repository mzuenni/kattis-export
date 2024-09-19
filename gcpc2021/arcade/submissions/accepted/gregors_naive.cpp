#include <iostream>
using namespace std;
using ll = long long;

ll naive(ll n)
{
	if (n == 1 || n == 3) return 1;
	for (int i = 0; i < 63; ++i)
		for (int j = i; j < 63; ++j)
			if (0LL + (1LL << i) + (1LL << j) + 1 == n)
				return (1LL << i) + 1;
	return -1;
}

int main()
{
	ll n; cin >> n;
	ll ans = naive(n);
	if (ans == -1) cout << "impossible" << endl;
	else cout << ans << endl;
}