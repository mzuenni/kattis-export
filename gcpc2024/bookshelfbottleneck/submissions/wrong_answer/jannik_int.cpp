#include <iostream>

using namespace std;

int main() {
	cin.tie(nullptr), ios::sync_with_stdio(false);
	int n, h;
	cin >> n >> h;
	int res = 0;
	bool ok = true;
	for (int i = 0; i < n; i++) {
		int x,y,z;
		cin >> x >> y >> z;
		int w = 1e9 + 1;
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
