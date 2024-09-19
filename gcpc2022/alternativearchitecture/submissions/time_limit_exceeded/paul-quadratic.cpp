#include <bits/stdc++.h>
using namespace std;
using i64 = long long;

int main() {
	i64 a, b;
	cin >> a >> b;
	a--, b--;
	if (a > b) swap(a,b);
	int res = 0;
	for (i64 x = 1; x <= a; x++) {
		for (i64 y = 0; y <= a; y++) {
			if (x*x + y*y == a*a) {
				res += b*y % a == 0 && b*x % a == 0;
			}
		}
	}
	if (a != b) res *= 2;
	cout << res << '\n';
}
