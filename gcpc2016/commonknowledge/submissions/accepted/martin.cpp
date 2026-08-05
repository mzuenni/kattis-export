#include <iostream>

using namespace std;

typedef long long ll;

ll foo(ll b, ll n)
{
	if(n == 0) return 1;
	if(n == 1) return b;
	if(n % 2 == 1) return foo(b, n-1) * b;
	ll x = foo(b, n/2);
	return x * x;
}

int main()
{
	ll n;
	cin >> n;
	ll base = 8;
	cout << foo(8,n) << "\n";	
	return 0;
}
