#include <bits/stdc++.h>

using namespace std;

struct Interval { int x, y_lo, y_hi; };
struct Point { int x, y; };

long long cross(const Point& a, const Point& b, const Point& c) {
	Point ab{ b.x - a.x, b.y - a.y }, ac{ c.x - a.x, c.y - a.y };
	return ab.x*1LL*ac.y - ab.y*1LL*ac.x;
}

void graham_update(deque<Point>& stack, const Point& p, int sign) {
	auto convex = [sign](auto a, auto b, auto c) {
		return sign * cross(a, b, c) > 0;
	};
	while (stack.size() > 1 && !convex(stack.end()[-2], stack.back(), p))
		stack.pop_back();
	stack.push_back(p);
}

vector<Point> solve(const Point& from, const Point& to,
		vector<Interval> intervals)
{
	intervals.push_back({ to.x, to.y, to.y });
	deque<Point> red{ from }, green{ from };
	vector<Point> ans{ from };
	for (auto& interval : intervals)
	{
		graham_update(red, { interval.x, interval.y_hi }, 1);
		graham_update(green, { interval.x, interval.y_lo }, -1);
		while (green.size() > 1 && red.size() > 1 &&
				cross(green[0], green[1], red[1]) <= 0) {
			red.pop_front(), green.pop_front();
			if (red[0].x < green[0].x)
				green.push_front(red[0]);
			else if (red[0].x > green[0].x)
				red.push_front(green[0]);
			ans.push_back(red[0]);
		}
	}
	return ans;
}

int main()
{
	ios_base::sync_with_stdio(false);
	Point from, to;
	cin >> from.x >> from.y >> to.x >> to.y;
	int n;
	cin >> n;
	vector<Interval> intervals(n);
	for (auto& i : intervals)
		cin >> i.x >> i.y_lo >> i.y_hi;
	for (auto& p : solve(from, to, intervals))
		cout << p.x << " " << p.y << "\n";
	return 0;
}
