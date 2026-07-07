#include <iostream>
#include <vector>
#include <utility>
#include <algorithm>
using namespace std;
#define pb push_back
#define mp make_pair

vector<pair<pair<int,int>,int>> points;
vector<pair<double,double>> polyA, polyB;

int main()
{
	int n;
	cin >> n;
	int min_x = 9999;
	int max_x = -9999;
	int min_y = 9999;
	int max_y = -9999;
	for (int i = 0; i < n; ++i)
	{
		int x,y,c;
		cin >> x >> y >> c;
		min_x = min(min_x, x);
		max_x = max(max_x, x);
		min_y = min(min_y, y);
		max_y = max(max_y, y);
		points.pb(mp(mp(x,y),c));
	}
	sort(points.begin(), points.end());

	int last_x = min_x;
	for (auto &p : points)
	{
		int x = p.first.first;
		int y = p.first.second;
		int c = p.second;
		
		if (x != last_x)
		{
			polyA.pb(mp(last_x - 0.1, max_y + 1.1));
			polyB.pb(mp(last_x + 0.1, max_y + 1));

			polyA.pb(mp(x - 0.4, max_y + 1.1));
			polyB.pb(mp(x - 0.5, max_y + 1));

			polyA.pb(mp(x - 0.4, min_y - 1));
			polyB.pb(mp(x - 0.5, min_y - 1.1));

			polyA.pb(mp(x - 0.1, min_y - 1));
			polyB.pb(mp(x + 0.1, min_y - 1.1));
		}

		if (c == 1)
		{
			polyA.pb(mp(x - 0.1, y));
			polyB.pb(mp(x + 0.1, y));
		}
		else if (c == 2) 
		{
			polyA.pb(mp(x - 0.2, y));
			polyB.pb(mp(x - 0.1, y));
		}
		else 
		{
			polyA.pb(mp(x + 0.1, y));
			polyB.pb(mp(x + 0.2, y));
		}
		last_x = x;
	}
	polyA.pb(mp(last_x - 0.1, max_y + 1.1));
	polyB.pb(mp(last_x + 0.1, max_y + 1));

	polyA.pb(mp(last_x + 1.1, max_y + 1.1));
	polyB.pb(mp(last_x + 1, max_y + 1));

	polyA.pb(mp(last_x + 1.1, min_y - 2.1));
	polyB.pb(mp(last_x + 1, min_y - 2));

	polyA.pb(mp(min_x - 0.1, min_y - 2.1));
	polyB.pb(mp(min_x + 0.1, min_y - 2));

	cout << polyA.size() << endl;
	for (pair<double,double> &p : polyA)
		cout << p.first << " " << p.second << endl;
	cout << polyB.size() << endl;
	for (pair<double,double> &p : polyB)
		cout << p.first << " " << p.second << endl;
}
