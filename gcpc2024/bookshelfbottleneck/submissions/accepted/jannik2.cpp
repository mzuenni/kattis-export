#include <algorithm>
#include <iostream>
#include <array>

using namespace std;

using i64 = int64_t;

int main() {
	cin.tie(nullptr), ios::sync_with_stdio(false);
	i64 n, h;
	cin >> n >> h;
	i64 res = 0;
	for (i64 i = 0; i < n; i++) {
		array<i64, 3> a;
		for (i64&x:a) cin >> x;
		sort(&a[0], &a[3]);
		if (a[0] > h) {
			cout << "impossible\n";
			return 0;
		}
		res += a[a[1] > h];
	}
	cout << res << '\n';
}
