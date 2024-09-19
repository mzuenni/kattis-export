// same idea as florian-cht, but instead of maintaining the lines
// using convex hull tricks, just iterate over all of them for every query
// divide & conquer can degenerate and cause O(n^2) runtime
// Using doubles, which possibly causes precision errors
#include <bits/stdc++.h>

using namespace std;
using ld = long double;

struct Constraint { int x, y_lo, y_hi; };
struct Point { int x, y; };
struct Line { int k, d; };

struct {
	vector<Line> lines;
	
	// return the l <= index < r of the line that's maximum at the given x and
	// the y-coordinate of the line at this x
	pair<int, ld> query(int l, int r, ld x) {
		pair<int, ld> opt{ -1, numeric_limits<ld>::lowest() };
		for (int i = l; i < r; i++)
			if (auto y = lines[i].k*x + lines[i].d; opt.second < y)
				opt = { i, y };
		return opt;
	}
} lower, upper;
vector<Constraint> constraints;
vector<Point> ans;

void solve_dc(Point from, Point to, int l, int r)
{
	if (l == r) {
		ans.push_back(from);
		return;
	}
	ld k = (to.y - from.y) / ld(to.x - from.x);
	ld d = from.y - k * from.x;
	auto [lo_i, lo_v] = lower.query(l, r, k);
	auto [hi_i, hi_v] = upper.query(l, r, k);
	if (lo_v + d < 0 && hi_v - d < 0) { // both on the wrong side => direct path
		ans.push_back(from);
		return;
	}
	int split;
	Point split_p;
	if (lo_v + d >= 0) {
		split = lo_i;
		split_p = { constraints[split].x, constraints[split].y_hi };
	} else {
		split = hi_i;
		split_p = { constraints[split].x, constraints[split].y_lo };
	}
	solve_dc(from, split_p, l, split);
	solve_dc(split_p, to, split+1, r);
}

void solve(Point from, Point to)
{
	vector<Line> l_lower, l_upper;
	for (auto& c : constraints) {
		l_lower.push_back({ c.x, -c.y_hi });
		l_upper.push_back({ -c.x, c.y_lo });
	}
	lower = { move(l_lower) }, upper = { move(l_upper) };
	solve_dc(from, to, 0, constraints.size());
	ans.push_back(to);
}

int main()
{
	ios_base::sync_with_stdio(false);
	Point from, to;
	cin >> from.x >> from.y >> to.x >> to.y;
	int n;
	cin >> n;
	constraints.resize(n);
	for (auto &c : constraints)
		cin >> c.x >> c.y_lo >> c.y_hi;
	solve(from, to);
	for (auto&p : ans)
		cout << p.x << " " << p.y << "\n";
	return 0;
}
