#include <bits/stdc++.h>
using namespace std;

int main() {
	long long x1, y1, r1, x2, y2, r2;
	cin >> x1 >> y1 >> r1 >> x2 >> y2 >> r2;

	if ((x1+y1+r1+x2+y2+r2)%2) {
		cout << "impossible" << endl;
		return 0;
	}

	long long xmin = max(x1-r1, x2-r2);
	long long xmax = min(x1+r1, x2+r2);

	for (long long x = xmin; x <= xmax; x++) {
		long long dy1 = r1 - abs(x-x1);
		long long dy2 = r2 - abs(x-x2);
		
		long long ymin = max(y1-dy1, y2-dy2);
		long long ymax = min(y1+dy1, y2+dy2);
		
		long long y = ymin;
		if ((x1+y1+r1+x+y) % 2) y++;

		if (y <= ymax) {
			cout << x << " " << y << endl;
			return 0;
		}
	}
	cout << "impossible" << endl;
}
