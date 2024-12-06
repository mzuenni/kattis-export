#include <iostream>
#include <assert.h>
#include <cmath>
#include <map>
using namespace std;

int query(int c, int r) {
	cout << "? " << c << ' ' << r << endl;
	int h;
	cin >> h;
	return h;
}

void ans(int c, int r) {
	cout << "! " << c << ' ' << r << endl;
}

int main() {
	cin.tie(0);
	ios_base::sync_with_stdio(0);

	int n;
	cin >> n;

	int c = query(n, 1);
	int r = (c < n ? query(n - c, 1) : 1);
	ans(c, r);

	return 0;
}
