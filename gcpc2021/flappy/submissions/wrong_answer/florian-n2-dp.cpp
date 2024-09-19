// O(n^2) dp (optimised version of florian-n3-dp)
// precision errors because of doubles
#include <bits/stdc++.h>

using namespace std;
using ld = long double;

const int MAX_N = 1000005;

ld dp[MAX_N][2];
pair<int,int> dp_from[MAX_N][2];

struct Interval { int x, y_lo, y_hi; };
struct Point { int x, y; };

vector<Interval> intervals;

long long cross(const Point& a, const Point& b, const Point& c) {
	Point ab{ b.x - a.x, b.y - a.y }, ac{ c.x - a.x, c.y - a.y };
	return ab.x*1LL*ac.y - ab.y*1LL*ac.x;
}

Point at(int i, bool top) {
	return { intervals[i].x, top ? intervals[i].y_hi : intervals[i].y_lo };
}

// is point p inside or on the cone defined by (a, down, up)?
bool inside(const Point& p, const Point& a, const Point& down, const Point& up) {
	return cross(a, down, p) <= 0 && cross(a, up, p) >= 0;
}

vector<Point> solve(const Point& from, const Point& to)
{
	intervals.insert(intervals.begin(), { from.x, from.y, from.y });
	intervals.push_back({ to.x, to.y, to.y });
	int n = intervals.size();
	dp_from[0][0] = dp_from[0][1] = { -1, 0 };
	for (int i = 1; i < n; i++)
		for (int s = 0; s < 2; s++) {
			Point p = at(i, s), down = at(i-1, 0), up = at(i-1, 1);
			dp[i][s] = numeric_limits<ld>::max();
			for (int j = i-1; j >= 0; j--) {
				if (cross(p, up, at(j, 0)) < 0 || cross(p, down, at(j, 1)) > 0)
					break;
				for (int sp = 0; sp < 2; sp++)
					if (auto pp = at(j, sp); inside(pp, p, down, up)) {
						auto here = dp[j][sp] + hypot(p.x - pp.x, p.y - pp.y);
						if (here < dp[i][s]) {
							dp[i][s] = here;
							dp_from[i][s] = { j, sp };
						}
						if (sp == 0)
							down = pp;
						else
							up = pp;
					}
			}
		}
	vector<Point> ans;
	for (int i = n-1, s = 0; i != -1; ) {
		ans.push_back(at(i, s));
		auto [ip, sp] = dp_from[i][s];
		i = ip, s = sp;
	}
	reverse(ans.begin(), ans.end());
	return ans;
}

int main()
{
	ios_base::sync_with_stdio(false);
	Point from, to;
	cin >> from.x >> from.y >> to.x >> to.y;
	int n;
	cin >> n;
	intervals.resize(n);
	for (auto& i : intervals)
		cin >> i.x >> i.y_lo >> i.y_hi;
	for (auto& p : solve(from, to))
		cout << p.x << " " << p.y << "\n";
	return 0;
}
