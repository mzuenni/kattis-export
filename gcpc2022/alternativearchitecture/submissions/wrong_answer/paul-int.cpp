#include <bits/stdc++.h>
using namespace std;

int main() {
	int a, b;
	cin >> a >> b;
	int res = 0;
	for (int x = a, y = 0; x > 0; x--) {
		while (x*x + y*y < a*a) y++;
		if (x*x + y*y == a*a) {
			res += b*y % a == 0 && b*x % a == 0;
		}
	}
	if (a != b) res *= 2;
	cout << res << '\n';
}
