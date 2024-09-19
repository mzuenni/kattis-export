#include <bits/stdc++.h>
using namespace std;
using i64 = long long;

int main() {
	i64 a, b;
	cin >> a >> b;
	a--, b--;
	int res = 0;
	for (i64 x = a, y = 0; x > 0; x--) {
		while (x*x + y*y < a*a) y++;
		if (x*x + y*y == a*a) {
			res += b*y % a == 0 && b*x % a == 0;
		}
	}
	if (a != b) res *= 2;
	cout << res << '\n';
}
