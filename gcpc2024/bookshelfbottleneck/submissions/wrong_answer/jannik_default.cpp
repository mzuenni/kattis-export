#include <iostream>

using namespace std;

using i64 = int64_t;

int main() {
	cin.tie(nullptr), ios::sync_with_stdio(false);
	i64 n, h;
	cin >> n >> h;
	i64 res = 0;
	for (i64 i = 0; i < n; i++) {
		i64 x,y,z;
		cin >> x >> y >> z;
		i64 w = 1.1e9;
		if (min(x,y) <= h)
			w = min(w, z);
		if (min(x,z) <= h)
			w = min(w, y);
		if (min(y,z) <= h)
			w = min(w, x);
		res += w;
	}
	if (res > 1e9)
		cout << "impossible\n";
	else
		cout << res << '\n';
}
