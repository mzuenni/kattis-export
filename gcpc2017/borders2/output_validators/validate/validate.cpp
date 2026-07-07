#include <bits/stdc++.h>
#include "validate.h"
using namespace std;

const int MAX_POINTS = 1000, COORD_MULTIPLIER = 100000, MAX_COORD = 3000;

struct point {
	long long x, y;
	int col;
};

long long ccw(point a, point b, point c) {
	long long cross = (b.x-a.x)*(c.y-b.y) - (c.x-b.x)*(b.y-a.y);
	return cross ? (cross > 0 ? 1 : -1) : 0;
}

bool on_segment(point a, point b, point c) { // is c on segment a-b?
	if (ccw(a,b,c)) return false;
	return min(a.x,b.x) <= c.x && c.x <= max(a.x,b.x) &&
	       min(a.y,b.y) <= c.y && c.y <= max(a.y,b.y);
}

bool segments_intersect(point a, point b, point c, point d) {
	if (on_segment(a,b,c) || on_segment(a,b,d) || on_segment(c,d,a) || on_segment(c,d,b))
		return true;
	return ccw(a,b,c)*ccw(a,b,d) < 0 && ccw(c,d,a)*ccw(c,d,b) < 0;
}

bool point_in_polygon(const vector<point> &poly, point a) {
	int winding = 0;
	for (int i = 0; i < poly.size(); i++) {
		point p = poly[i], q = poly[(i+1) % poly.size()];
		
		if (on_segment(p,q,a))
			wrong_answer("Polygon passes through the point (%d,%d).\n", a.x, a.y);
		
		if (p.y <= a.y) {
			if (q.y > a.y && ccw(p,q,a) > 0) winding++;
		} else {
			if (q.y <= a.y && ccw(p,q,a) < 0) winding--;
		}
	}
	if (abs(winding) > 1)
		judge_error("Encountered winding number of %d!\n", winding);
	return winding;
}

long long read_coord() {
	double xx;
	if (!(author_out >> xx))
		wrong_answer("Expected a floating point number.\n");
	long long x = llround(xx * COORD_MULTIPLIER);
	if (abs(x) > MAX_COORD * COORD_MULTIPLIER)
		wrong_answer("Received a coordinate outside of the range [-%d,%d].\n",
		                 MAX_COORD, MAX_COORD);
	return x;
}

vector<point> read_polygon() {
	int n;
	if (!(author_out >> n))
		wrong_answer("Expected an integer, the number of points.\n");
	if (n < 3 || n > MAX_POINTS)
		wrong_answer("Polygon has invalid number of points %d (should be in range [3,%d]).\n",
		                 n, MAX_POINTS);
	
	vector<point> p(n);
	for (int i = 0; i < n; i++) {
		p[i].x = read_coord();
		p[i].y = read_coord();
	}
	
	for (int i = 0; i < n; i++)
		for (int j = i+2; j < n; j++) {
			if ((j+1) % n == i) continue;
			if (segments_intersect(p[i],p[i+1],p[j],p[(j+1)%n]))
				wrong_answer("Polygon is self-intersecting.\n");
		}
	
	for (int i = 0; i < n; i++) {
		if (on_segment(p[i],p[(i+1)%n],p[(i+2)%n]) || on_segment(p[(i+1)%n],p[(i+2)%n],p[i]))
			wrong_answer("Polygon is self-intersecting.\n");
	}

	return p;
}

int main(int argc, char **argv) {
	init_io(argc,argv);
	
	int n;
	judge_in >> n;

	vector<point> a(n);
	for (int i = 0; i < n; i++) {
		int x, y, c;
		judge_in >> x >> y >> c;
		a[i] = {x*COORD_MULTIPLIER, y*COORD_MULTIPLIER, c};
	}
	
	vector<point> p = read_polygon(), q = read_polygon();
	
	for (int i = 0; i < p.size(); i++)
		for (int j = 0; j < q.size(); j++) {
			if (segments_intersect(p[i],p[(i+1)%p.size()],q[j],q[(j+1)%q.size()]))
				wrong_answer("The two polygons intersect.\n");
		}

	map<int,pair<bool,bool>> in_out;
	
	for (int i = 0; i < n; i++) {
		pair<bool,bool> cur = {point_in_polygon(p,a[i]), point_in_polygon(q,a[i])};
		
		if (in_out.find(a[i].col) == end(in_out))
			in_out[a[i].col] = cur;

		if (in_out[a[i].col] != cur)
			wrong_answer("Two points of equal colour are separated by one of the polygons.\n");
	}
	
	for (int c = 1; c <= 3; c++)
		for (int d = c+1; d <= 3; d++) {
			if (in_out[c] == in_out[d])
				wrong_answer("The colours %d and %d are not separated by the polygons.\n",
				                 c, d);
		}

	accept();
}

