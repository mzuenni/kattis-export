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
	ll d = d1;
	ll dx = x1 < x2 ? min(x2-x1,d) : max(x2-x1,-d);
	d -= abs(dx);
	ll dy = y1 < y2 ? min(y2-y1,d) : max(y2-y1,-d);
	if (abs(dx+dy) % 2 != d1 % 2)
		dx = dx > 0 ? dx-1 : dx+1;
	cout << x1 + dx << " " << y1 + dy << endl;
}
