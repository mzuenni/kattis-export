#include <bits/stdc++.h>
using namespace std;

int main() {
	int t;
	cin >> t;
	int res = 0;
	if (t > 600) res = t - 600;
	else if (t > 540) res = 45;
	else if (t > 360) res = 30;
	cout << res << endl;
}
