#include <iostream>

using namespace std;

bool legal(int w, int br)
{
	if (w > 6*60 and br < 30) return false;
	if (w > 9*60 and br < 45) return false;
	return true;
}

int main()
{
	int t, res = 1e6;
	cin >> t;
	for (int w = 0; w <= min(t, 10*60); w++) {
		int br = t - w;
		if (legal(w, br))
			res = br;
	}
	cout << res << endl;
}
