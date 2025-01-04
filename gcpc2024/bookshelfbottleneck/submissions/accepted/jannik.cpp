#include <iostream>

using namespace std;

using i64 = int64_t;

int main() {
	cin.tie(nullptr), ios::sync_with_stdio(false);
	i64 n, h;
	cin >> n >> h;
	i64 res = 0;
	bool ok = true;
	for (i64 i = 0; i < n; i++) {
		i64 x,y,z;
		cin >> x >> y >> z;
		i64 w = 1e9 + 1;
		if (min(x,y) <= h)
			w = min(w, z);
		if (min(x,z) <= h)
			w = min(w, y);
		if (min(y,z) <= h)
			w = min(w, x);
		ok &= w <= 1e9;
		res += w;
	}
	if (ok)
		cout << res << '\n';
	else
		cout << "impossible\n";
}
