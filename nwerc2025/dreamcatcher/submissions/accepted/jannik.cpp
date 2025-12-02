#include <iostream>
#include <numeric>

using namespace std;

int main()
{
	int n, k;
	cin >> n;
	for (k = n / 2; gcd(n,k) != 1; k--);
	cout << k << endl;
}
