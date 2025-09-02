#include <iostream>
#include <iomanip>
using namespace std;

int main()
{
	int n,c; cin >> n >> c;
	int sec = 0;
	for (int i = 0; i < n; ++i)
	{
		int m; char z; int s;
		cin >> m >> z >> s;
		sec += m * 60 + s;
	}
	sec -= (n-1) * c;
	int hh = sec/60/60;
	int mm = sec/60%60;
	int ss = sec%60;
	cout << setfill('0') << setw(2) << hh << ":"
		<< setfill('0') << setw(2) << mm << ":"
		<< setfill('0') << setw(2) << ss;
}
