#include "validation.h"
#include <vector>
using namespace std;
using i64 = long long;

const int N = 500'000;
const int X = 1'000'000;
const int P = 1'000'000;

struct point {
	int x, y;
};

point operator-(point a, point b) {
	return {a.x-b.x, a.y-b.y};
}

i64 operator*(point a, point b) { // dot product
	return i64(a.x)*b.x + i64(a.y)*b.y;
}

i64 operator%(point a, point b) { // cross product
	return i64(a.x)*b.y - i64(a.y)*b.x;
}

bool isH(point a, point b) {
	return a.x != b.x && a.y == b.y;
}

bool isV(point a, point b) {
	return a.x == b.x && a.y != b.y;
}

void read_point(InputValidator &v, point &a) {
	a.x = v.read_integer("x", -X, X);
	v.space();
	a.y = v.read_integer("y", -X, X);
	v.newline();
}

void check_polygon(InputValidator &v, vector<point> a) {
	int n = size(a);
	
	vector<tuple<int,int,int>> events;
	for (int i = 0; i < n; i++) {
		point p = a[i], q = a[(i+1)%n];
		if (p.x == q.x) {
			events.emplace_back(p.x, 0, i);
		} else {
			if (p.x > q.x) swap(p,q);
			events.emplace_back(p.x, -1, i);
			events.emplace_back(q.x, 1, i);
		}
	}
	sort(begin(events), end(events));

	set<int> ys;
	for (auto [_,t,i]: events) {
		if (t == 0) {
			int y1 = a[i].y, y2 = a[(i+1)%n].y;
			if (y1 > y2) swap(y1,y2);
			auto it1 = ys.find(y1);
			assert(it1 != end(ys));
			auto it2 = ys.find(y2);
			assert(it2 != end(ys));
			v.check(next(it1) == it2, "edges must not intersect");
		} else if (t == -1) {
			v.check(ys.insert(a[i].y).second, "edges must not intersect");
		} else {
			assert(ys.contains(a[i].y));
			ys.erase(a[i].y);
		}
	}
}

bool between(point a, point b, point p) {
	return (a-p)*(b-p) < 0 && (b-a)%(p-a) == 0;
}

int main(int argc, char **argv) {
	ifstream in(argv[1]);
	InputValidator v(argc, argv);

	int n = v.read_integer("n", 1, N);
	v.space();
	int m = v.read_integer("m", 1, N);
	v.newline();

	vector<point> a(n);
	for (int i = 0; i < n; i++) {
		read_point(v, a[i]);
		v.check(a[i].x%2 == 0 && a[i].y%2 == 0, "vertex coordinates must be even");
	}

	point s;
	read_point(v, s);
	v.check((s.x+s.y)%2 != 0, "exactly one coordinate of the start point must be even");

	for (int i = 0; i < n; i++) {
		point p = a[i], q = a[(i+1)%n], r = a[(i+2)%n];
		v.check(isH(p,q) || isV(p,q), "edges must be vertical or horizontal");
		v.check(isH(p,q) != isH(q,r), "must alternate between vertical and horizontal edges");
	}

	check_polygon(v, a);

	i64 perim = 0, area = 0;
	for (int i = 0; i < n; i++) {
		point p = a[i], q = a[(i+1)%n];
		perim += abs(p.x-q.x) + abs(p.y-q.y);
		area += p%q;
	}
	v.check(perim <= P, "perimeter must not exceed ", P, ", but is ", perim);
	v.check(area > 0, "vertices must be in counterclockwise order");

	bool found_side = false;
	for (int i = 0; i < n; i++) {
		point p = a[i], q = a[(i+1)%n];
		if (between(p, q, s)) {
			found_side = true;
			point t = {s.x+1, s.y+1};
			v.check((q-p)%(t-p) > 0, "ray must point inside the polygon");
		}
	}

	v.check(found_side, "starting point must be on polygon boundary");
}

