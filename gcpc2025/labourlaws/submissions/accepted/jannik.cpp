#include <iostream>

using namespace std;

int main()
{
	int t, res = 1e6;
	cin >> t;
	for (int w = 0; w <= min(10*60, t); w++) {
		int br = 0;
		if (w > 6 * 60) br = 30;
		if (w > 9 * 60) br = 45;
		res = min(res, max(w + br, t) - w);
	}
	cout << res << endl;
}
