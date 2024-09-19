// for every three consecutive intervals a, b, c, consider the line segments
// s1 = (a.x, a.y1) to (c.x, c.y1) and s2 = (a.x, a.y2) to (c.x, c.y2). If
// 	- b.y1 is below s1 and b.y2 above s2 => remove b
//	- b.y1 is above s2 => replace b with the point-interval (b.x, b.y1)
//	- b.y2 is below s1 => replace b with the point-interval (b.x, b.y2)
// start and end are treated as length 0 intervals.
// Iterate this process while there are three such intervals. If only points
// remain, this is the solution. But this is not always the case
// O(n)
#include <bits/stdc++.h>

using namespace std;

struct Interval { int x, y_lo, y_hi; };
struct Point { int x, y; };
struct Rational {
	long long a, b;
	bool operator<=(int x) { return a <= b*x; }
	bool operator>=(int x) { return a >= b*x; }
};
struct Line {
	Point a, b;
	Line(const Point& a, const Point& b) : a(a), b(b) { }
	Rational operator()(int x) {
		long long dy = b.y - a.y, dx = b.x - a.x;
		return {(x - a.x)*dy + a.y*dx, dx};
	}
};

bool subsumed(Interval& a, Interval& b, Interval& c) {
	Line l_lo({a.x, a.y_lo}, {c.x, c.y_lo});
	Line l_hi({a.x, a.y_hi}, {c.x, c.y_hi});
	return l_lo(b.x) >= b.y_lo && l_hi(b.x) <= b.y_hi;
}

optional<Interval> reduce(Interval& a, Interval& b, Interval& c) {
	Line l_lo({a.x, a.y_lo}, {c.x, c.y_lo});
	Line l_hi({a.x, a.y_hi}, {c.x, c.y_hi});
	if (l_lo(b.x) >= b.y_hi)
		return Interval{b.x, b.y_hi, b.y_hi};
	if (l_hi(b.x) <= b.y_lo)
		return Interval{b.x, b.y_lo, b.y_lo};
	return nullopt;
}

list<Interval> magic;

void simplify(list<Interval>::iterator it, Interval& i)
{
	while (it != magic.begin() && subsumed(*prev(it), *it, i))
		it = prev(magic.erase(it));
	if (it != magic.begin())
		if (auto p = reduce(*prev(it), *it, i)) {
			*it = *p;
			simplify(prev(it), *it);
		}
}

vector<Point> solve(Point& from, Point& to, vector<Interval>& intervals)
{
	magic.push_back({from.x, from.y, from.y});
	intervals.push_back({to.x, to.y, to.y});
	for (auto& i : intervals) {
		simplify(prev(magic.end()), i);
		magic.push_back(i);
	}
	vector<Point> ans;
	for (auto& i : magic)
		ans.push_back({ i.x, i.y_lo });
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
