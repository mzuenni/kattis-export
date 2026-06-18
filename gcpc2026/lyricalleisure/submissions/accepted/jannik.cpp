#include <iostream>

using namespace std;

int main()
{
	int n, k;
	cin >> n >> k;
	for (int i = 0; i < k; i++)
		cout << 'a';
	for (int i = k; i < n; i++)
		cout << char('b' + (i % 25));
	cout << '\n';
}
