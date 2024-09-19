// O(nlog^2(n)) with segmenttree of convex hull tricks
// Using doubles, which possibly causes precision errors
#include <bits/stdc++.h>

using namespace std;
using ld = long double;

struct Constraint { int x, y_lo, y_hi; };
struct Point { int x, y; };
struct Line { int k, d; };

struct LineTree
{
	struct Item : Line { int index; };
	int n;
	vector<vector<Item>> tree;
	
	LineTree(const vector<Line>& lines = {}) :
		n(lines.size()), tree(2*n)
	{
		for (int i = 0; i < n; i++) // leafs
			tree[i + n].push_back({ lines[i], i });
		for (int i = n-1; i > 0; i--) { // merge sort tree
			auto &l = tree[2*i], &r = tree[2*i+1], &p = tree[i];
			p.resize(l.size() + r.size());
			merge(l.begin(), l.end(), r.begin(), r.end(), p.begin(),
					[](Item& a, Item& b) { return a.k < b.k; });
		}
		auto bad = [](Item &a, Item &b, Item &c) { // no 2 slopes are the same
			return (c.d - a.d)*1LL*(a.k - b.k) <= (b.d - a.d)*1LL*(a.k - c.k);
		};
		for (int i = 1; i < n; i++) { // build convex hull in every vertex
			auto &hull = tree[i];
			int j = 0;
			for (auto &item : hull) {
				while (j > 1 && bad(hull[j-2], hull[j-1], item))
					j--;
				hull[j++] = item;
			}
			hull.resize(j);
		}
	}

	// return the l <= index < r of the line that's maximum at the given x and
	// the y-coordinate of the line at this x
	pair<int, ld> query(int l, int r, ld x) {
		auto query_hull = [x](vector<Item>& hull) {
			return *lower_bound(hull.begin(), hull.end(), x,
				[&](Item &a, ld x) {
					if (&a == &hull.back()) // last line has an open interval
						return false;
					Item &b = *(&a + 1);
					return (a.k - b.k)*x < b.d - a.d;
				});
		};
		pair<int, ld> opt{ -1, numeric_limits<ld>::lowest() };
		auto relax = [&](const Item &item) {
			if (auto y = item.k*x + item.d; opt.second < y)
				opt = { item.index, y };
		};
		for (l += n, r += n; l < r; l /= 2, r /= 2) {
			if (l & 1)
				relax(query_hull(tree[l++]));
			if (r & 1)
				relax(query_hull(tree[--r]));
		}
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
	lower = l_lower, upper = l_upper;
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
