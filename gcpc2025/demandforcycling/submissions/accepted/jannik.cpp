#include <iostream>

using namespace std;

constexpr int oo = 0x3f3f3f3f;

int main()
{
	int n;
	cin >> n;
	int maxx = -oo, minx = oo, maxy = -oo, miny = oo;
	while (n-- > 0) {
		int x, y;
		cin >> x >> y;
		maxx = max(maxx, x), minx = min(minx, x);
		maxy = max(maxy, y), miny = min(miny, y);
	}
	cout << "4\n";
	cout << maxx << ' ' << miny << '\n';
	cout << maxx << ' ' << maxy << '\n';
	cout << minx << ' ' << maxy << '\n';
	cout << minx << ' ' << miny << '\n';
}
