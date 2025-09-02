#include <iostream>
#include <algorithm>
#include <string>
#include <cmath>
#include <vector>
#include <sstream>
#include <stack>
#include <queue>
#include <map>
#include <climits>
#include <cstdio>
#include <set>
#include <unordered_map>
#include <unordered_set>
#include <iomanip>
#include <functional>
#include <bitset>
#include <cctype>
#include <cassert>
using namespace std;
#ifdef DEBUG
#define db(a) (cout << (#a) << " = " << (a) << endl)
#else
#define db(a)
#endif
using ll = long long;

struct Point
{
	double x;
	double y;
};

struct Circle
{
	Point mid;
	double r;
};

double dist(const Point& p1, const Point& p2)
{
	return sqrt((p2.x - p1.x) * (p2.x - p1.x) + (p2.y - p1.y) * (p2.y - p1.y));
}

double dot(const Point& a, const Point& b)
{
	return a.x * b.x + a.y * b.y;
}

double length_circle_segment(const Circle& c, const double alpha)
{
	return static_cast<double>(c.r) * alpha;
}

double angle(const Point& a, const Point& o, const Point& b)
{
	double oa = dist(o, a);
	double ob = dist(o, b);
	Point v1 = {(o.x - a.x) / oa, (o.y - a.y) / ob};
	Point v2 = {(o.x - b.x) / ob, (o.y - b.y) / ob};
	return acos(dot(v1, v2));
}

Point mid_point(const Point& p1, const Point& p2)
{
	return {(p1.x+p2.x)/2.0, (p1.y+p2.y)/2.0};
}

vector<Point> intersect_circles(const Circle& c1, const Circle& c2)
{
	vector<Point> ret;
	double c = dist(c1.mid, c2.mid);
	if(c == 0.0) return ret;
	double x = ((c1.r * c1.r) + (c * c) - (c2.r * c2.r)) / (2.0 * c);
	if((x*x) > (c1.r * c1.r)) return ret;
	double y = sqrt((c1.r * c1.r) - (x * x));
	Point e1 = {(c2.mid.x - c1.mid.x) / c, (c2.mid.y - c1.mid.y) / c};
	Point e2 = {-e1.y, e1.x};
	Point q1 = {c1.mid.x + x * e1.x + y * e2.x, c1.mid.y + x * e1.y + y * e2.y};
	Point q2 = {c1.mid.x + x * e1.x - y * e2.x, c1.mid.y + x * e1.y - y * e2.y};
	ret.push_back(q1);
	if(y != 0.0) ret.push_back(q2);
	return ret;
}

vector<Point> tangents(const Point& p, const Circle& c)
{	
	Point M = mid_point(p, c.mid);
	Circle Mc = {M.x, M.y, dist(p, M)};
	db(Mc.mid.x); db(Mc.mid.y); db(Mc.r);
	auto B = intersect_circles(Mc, c);
	db(B.size());
	assert(B.size() == 2);
	return B;
}

// 1: outside, 0: on perimeter, -1: inside
int inside_circle(const Point& p, const Circle& c)
{
	double dx = p.x - c.mid.x;
	double dy = p.y - c.mid.y;
	double res = dx*dx + dy*dy - c.r*c.r;
	return res ? (res > 0 ? 1 : -1) : 0;
}

bool line_circle_intersection(Point l1, Point l2, Circle c)
{
	l1.x -= c.mid.x; l1.y -= c.mid.y;
	l2.x -= c.mid.x; l2.y -= c.mid.y;
	c.mid = {0.0, 0.0};
	const Point d = {l2.x - l1.x, l2.y - l1.y};
	const double D = l1.x * l2.y - l2.x * l1.y;
	return (((c.r * c.r) * (d.x * d.x + d.y * d.y)) - (D * D)) > 0.0;
}

bool project_on_segment(const Point& start, const Point& end, const Point& p)
{
	const double d = dist(start, end);
	Point b = {(end.x - start.x) / d, (end.y - start.y) / d};
	Point a = {p.x - start.x, p.y - start.y};
	double dot = a.x * b.x + a.y * b.y;
	if(dot <= 0.0) return false;
	if(dot >= d) return false;
	return true;
}

int main()
{
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  Circle blue, red;
	Point start, end;
	cin >> start.x >> start.y;
	cin >> end.x >> end.y;
	cin >> blue.mid.x >> blue.mid.y >> blue.r;
	cin >> red.mid.x >> red.mid.y >> red.r;

	constexpr double MAX = 1000.0;
	auto inrange = [](const Point& p) { return p.x >= -MAX && p.x <= MAX && p.y >= -MAX && p.y <= MAX; };
	if(!inrange(start) || !inrange(end) || !inrange(blue.mid) || !inrange(red.mid))
	{
		std::cerr << "Point out of range\n";
		return -1;	
	}
	if(blue.r < 1 || blue.r > MAX || red.r < 1 || red.r > MAX)
	{
		std::cerr << "Radius out of range\n";
		return -1;	
	}	
	if(inside_circle(start, blue) != -1 || inside_circle(end, blue) != -1)
	{
		std::cerr << "Point outside blue circle\n";
		return -1;	
	}
	if(inside_circle(red.mid, blue) != -1)
	{
		std::cerr << "Red circles mid point outside blue circle\n";
		return -1;	
	}
	if((dist(blue.mid, red.mid) + red.r) > blue.r - 1e-9)
	{
		std::cerr << "Red circle overlaps blue circle\n";
		return -1;
	}
	if(inside_circle(start, red) != 1 || inside_circle(end, red) != 1)
	{
		std::cerr << "Point inside red circle\n";
		return -1;
	}	
	if(!line_circle_intersection(start, end, red))
	{
		std::cerr << "Red circle does not intersect start-end line\n";
		return -1;
	}	
	if(!project_on_segment(start, end, red.mid))
	{
		std::cerr << "Red circles mid point is not projected on start-end segment\n";
		return -1;
	}	
	
  return 42;
}
