#include <iostream>
#include <map>

using namespace std;

using pii = pair<int, int>;

map<pii, int> placed;

bool flip = false;

int get(int x, int y)
{
	return placed[pii(x, y)];
}
pii place(int x, int y)
{
	if (flip)
		swap(x, y);
	placed[pii(x, y)] = 1;
	cout << x << ' ' << y << endl;
	cin >> x >> y;
	if (x == 0 and y == 0)
		exit(0);
	placed[pii(x, y)] = 2;
	return pii(x, y);
}

int main()
{
	auto[x, y] = place(30, 30);
	flip = y == 30;
	place(31, 30);
	place(get(32, 30) ? 29 : 32, 30);
	exit(-1);
}
