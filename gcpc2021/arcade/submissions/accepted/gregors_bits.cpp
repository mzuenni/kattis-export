#include <iostream>
using namespace std;
using ll = long long;

int main()
{
	ll n; cin >> n;
	ll x = n;
	ll cnt = 0;
	while (x &= (x-1)) cnt++;
	if (cnt > 2) cout << "impossible" << endl;
	else cout << ((n-1) & (n-2)) + 1 << endl;
}