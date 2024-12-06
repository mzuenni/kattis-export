#include <algorithm>
#include <cstdio>
#include <vector>
using namespace std;

struct point {
	int x, y;
	point (int x0, int y0) {
		x = x0;
		y = y0;
	}
};

vector<point> P;

bool cmp_x_asc (const point& a, const point& b) {
	return a.x < b.x || (a.x == b.x && a.y < b.y);
}

bool cmp_x_desc (const point& a, const point& b) {
	return a.x > b.x || (a.x == b.x && a.y < b.y);
}

bool cmp_y_asc (const point& a, const point& b) {
	return a.y < b.y || (a.y == b.y && a.x < b.x);
}

bool cmp_y_desc (const point& a, const point& b) {
	return a.y > b.y || (a.y == b.y && a.x < b.x);
}

// Check if last point (just moved) is same as another; if so, remove
void remove_overlapping (int& n) {
	for (int i = 0; i < n-1; i++)
		if (P[i].x == P[n-1].x && P[i].y == P[n-1].y) {
			P.pop_back();
			n--;
			break;
		}
}

int main()
{
	for (int i = 0; i < 5; i++) {
		int x, y;
		scanf("%d %d", &x, &y);
		P.push_back(point(x, y));
	}
	int n = 5;
	int ans = 0;

	while (true) {
		bool something_changed = false;

		// Move leftmost location right
		sort(P.begin(), P.end(), &cmp_x_asc);
		if (P[n-1].x != P[n-2].x) {
			ans += P[n-1].x - P[n-2].x;
			P[n-1].x = P[n-2].x;
			remove_overlapping(n);
			if (n == 1)
				break;
			something_changed = true;
		}

		// Move rightmost location left
		sort(P.begin(), P.end(), &cmp_x_desc);
		if (P[n-1].x != P[n-2].x) {
			ans += P[n-2].x - P[n-1].x;
			P[n-1].x = P[n-2].x;
			remove_overlapping(n);
			if (n == 1)
				break;
			something_changed = true;
		}

		// Move up location down
		sort(P.begin(), P.end(), &cmp_y_asc);
		if (P[n-1].y != P[n-2].y) {
			ans += P[n-1].y - P[n-2].y;
			P[n-1].y = P[n-2].y;
			remove_overlapping(n);
			if (n == 1)
				break;
			something_changed = true;
		}

		// Move down location up
		sort(P.begin(), P.end(), &cmp_y_desc);
		if (P[n-1].y != P[n-2].y) {
			ans += P[n-2].y - P[n-1].y;
			P[n-1].y = P[n-2].y;
			remove_overlapping(n);
			if (n == 1)
				break;
			something_changed = true;
		}

		if (!something_changed)
			break;
	}

	// We are now left with one of these:
	// - 1 point (done)
	// - 4 points in a rectangle
	// - 5 points on a rectangle
	// - 5 points, 4 in a rectangle, 5th inside
	if (n >= 4) {
		sort(P.begin(), P.end(), &cmp_x_asc);
		int xmin = P[0].x;
		int xmax = P[n-1].x;
		sort(P.begin(), P.end(), &cmp_y_asc);
		int ymin = P[0].y;
		int ymax = P[n-1].y;
		int dx = xmax - xmin;
		int dy = ymax - ymin;
		ans += 2*dx + 2*dy; // Add rectangle
		if (n == 5 && P[2].x > xmin && P[2].x < xmax && P[2].y > ymin && P[2].y < ymax)
			// Fifth point inside
			ans += min(dx, dy); // Span entire height or width of rectangle
	}

	printf("%d\n", ans);
	return 0;
}
