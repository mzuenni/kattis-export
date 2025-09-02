#include <iostream>
using namespace std;

const int MAX_N = 300000;
int x[MAX_N];
int y[MAX_N];

int main()
{
	int n,m;
	cin >> n >> m;
	for (int i = 0; i < n; ++i)
		cin >> x[i];
	for (int i = m; i < n; ++i)
		y[i] = max(y[i-1], y[i-m] + x[i]);
	cout << y[n-1] << endl;
}