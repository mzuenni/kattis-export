#include <iostream>
#include <algorithm>
using namespace std;
using ll = long long;

int main()
{
	ll x1,y1,d1,x2,y2,d2;
	cin >> x1 >> y1 >> d1 >> x2 >> y2 >> d2;
	if (d1 > d2)
		swap(x1,x2), swap(y1,y2), swap(d1,d2);
	ll diff = abs(x1-x2) + abs(y1-y2);
	if (diff > d1+d2 || abs(x1 + y1 + d1) % 2 != abs(x2 + y2 + d2) % 2)
	{
		cout << "impossible" << endl;
		return 0;
	}
	if (diff <= d1)
		cout << x2 << " " << y2 << endl;
	else
	{
		ll dx = x1 < x2 ? min(x2-x1,d1) : max(x2-x1,-d1);
		d1 -= abs(dx);
		ll dy = y1 < y2 ? min(y2-y1,d1) : max(y2-y1,-d1);
		cout << x1 + dx << " " << y1 + dy << endl;
	}
}
