#include <algorithm>
#include <math.h>
#include <stdio.h>

using namespace std;

#define MAX 300
#define MAX_P (MAX*MAX)
#define MIN_P 10
#define MAX_SINGLE 666
const double eps = 1e-9;
#define FOR(i,a,b) for (int i = (a); i < (b); i++)
#define ABS(x) ((x) > 0 ? (x) : (-(x)))

typedef struct {
	int x, y, r;
} circle;

struct Point {
	double x, y;
	int id;
};

int ccw(Point p0, Point p1, Point p2) {
	double c = (p1.x - p0.x) * (p2.y - p0.y) - (p2.x - p0.x) * (p1.y - p0.y);
	if (ABS(c) <= eps) return 0;
	return (c > 0) ? 1 : -1;
}

double distPointPoint(Point p0, Point p1) {
    double dx = p0.x - p1.x, dy = p0.y - p1.y;
    return sqrt(dx*dx + dy*dy);
}

Point ref;
circle circles[MAX];
int pointsOnCircle[MAX];
Point points[MAX_P + MAX];

bool operator<(Point a, Point b) {
	if (int c = ccw(ref, a, b)) return c == 1;
	return distPointPoint(ref, a) < distPointPoint(ref, b);
}

int convex_hull(Point *pts, int n, Point *hull) {
	FOR(i, 0, n) {
		hull[i] = pts[i];
		if (ABS(hull[i].y - hull[0].y) < eps) {
			if (hull[i].x < hull[0].x) swap(hull[i], hull[0]);
		} else {
			if (hull[i].y < hull[0].y) swap(hull[i], hull[0]);
		}
	}
	ref = hull[0];
	sort(hull + 1, hull + n);
	int nhull = 2;
	FOR(i, 2, n) {
		hull[nhull++] = hull[i];
		while (ccw(hull[nhull-3], hull[nhull-2], hull[nhull-1]) <= 0) {
			hull[nhull-2] = hull[nhull-1];
			if (--nhull < 3) break;
		}
	}
	return nhull;
}

int
main(int argc, char **argv)
{
	int numCases;
	scanf("%d", &numCases);

	while (numCases --> 0) {
		int numCircles;
		scanf("%d", &numCircles);

		double totR = 0.;
		for (int i = 0; i < numCircles; i++) {
			scanf("%d%d%d", &circles[i].x, &circles[i].y, &circles[i].r);
			pointsOnCircle[i] = MIN_P;
			totR += circles[i].r;
		}
		int totalPts = 0;
		int ptsToDistribute = MAX_P - (MIN_P * numCircles);
		for (int i = 0; i < numCircles; i++) {
			double part = circles[i].r / totR;
			pointsOnCircle[i] += (int) (part * ptsToDistribute);
			pointsOnCircle[i] = min(MAX_SINGLE, pointsOnCircle[i]);
			double angle = 0.;
			double delta = 2.*M_PI/pointsOnCircle[i];
			for (int j = 0; j < pointsOnCircle[i]; j++, totalPts++, angle += delta) {
				points[totalPts].x = circles[i].x + circles[i].r * sin(angle);
				points[totalPts].y = circles[i].y + circles[i].r * cos(angle);
				points[totalPts].id = i;
			}
		}

		int convPts = convex_hull(points, totalPts, points);
		double sum = 0.0;
		for (int i = 0; i < convPts; i++) {
			double s = distPointPoint(points[i], points[(i + 1) % convPts]);
			if (points[i].id == points[(i + 1) % convPts].id) {
				sum += 2. * asin(s/(2.*circles[points[i].id].r)) * circles[points[i].id].r;
			} else {
				sum += s;
			}
		}

		printf("%12.12lf\n", sum);
	}

	return 0;
}
