#include <algorithm>
#include <cmath>
#include <iomanip>
#include <iostream>
#include <vector>

using ld = long double;
const ld LIM = 1e9L;
const ld EPS = 1e-7L;

int sgn(ld x) {
	return (x > 0) - (x < 0);
}

struct Point {
	ld x, y;
	Point operator+(Point p) const { return Point{x + p.x, y + p.y}; }
	Point operator-(Point p) const { return Point{x - p.x, y - p.y}; }
	Point operator/(ld d) const { return Point{x / d, y / d}; }
	Point operator*(ld d) const { return Point{x * d, y * d}; }
	ld dist() const { return std::sqrt(x * x + y * y); }
	ld cross(Point p) const { return x * p.y - y * p.x; }
	ld cross(Point a, Point b) const { return (a - *this).cross(b - *this); }
	Point unit() const { return *this / dist(); }
};

ld lineDist(const Point& a, const Point& b, const Point& p) {
	return (ld) (b - a).cross(p - a) / (b - a).dist();
}

int sideOf(Point s, Point e, Point p) {
	return sgn(s.cross(e, p));
}

int sideOf(Point s, Point e, std::pair<int, int> p) {
	return sgn(s.cross(e, {ld(p.first), ld(p.second)}));
}

int main() {
	std::ios::sync_with_stdio(false);
	std::cin.tie(nullptr);
	std::cout << std::fixed << std::setprecision(16);

	int n;
	std::cin >> n;

	std::vector<std::pair<int, int>> a(n), b(n);

	long long sumAx = 0;
	long long sumAy = 0;
	long long sumBx = 0;
	long long sumBy = 0;

	for (int i = 0; i < n; ++i) {
		std::cin >> a[i].first >> a[i].second;
		sumAx += a[i].first;
		sumAy += a[i].second;
	}

	for (int i = 0; i < n; ++i) {
		std::cin >> b[i].first >> b[i].second;
		sumBx += b[i].first;
		sumBy += b[i].second;
	}

	// centers of mass
	Point c{1.0L * sumAx / n, 1.0L * sumAy / n};
	Point d{1.0L * sumBx / n, 1.0L * sumBy / n};
	
	// points on the mirror
	Point e{0.5L * (c.x + d.x), 0.5L * (c.y + d.y)};
	Point f{e.x + (d.y - c.y), e.y - (d.x - c.x)};

	// chandeliers are on different sides of mirror?
	if (sideOf(e, f, a[0]) == sideOf(e, f, b[0])) {
		std::cout << "impossible" << '\n';
		return 0;
	}
	for (int i = 1; i < n; ++i) {
		if (sideOf(e, f, a[0]) != sideOf(e, f, a[i])) {
			std::cout << "impossible" << '\n';
			return 0;
		}
		if (sideOf(e, f, b[0]) != sideOf(e, f, b[i])) {
			std::cout << "impossible" << '\n';
			return 0;
		}
	}

	// chandeliers are mirrored onto each other?
	Point dir = (d - c).unit();
	std::vector<std::pair<int, int>> a2(n);
	for (int i = 0; i < n; ++i) {
		Point p{ld(a[i].first), ld(a[i].second)};
		ld dist = lineDist(e, f, p);
		p.x -= 2.0L * dir.x * dist;
		p.y -= 2.0L * dir.y * dist;
		if (p.x > 1e9 || p.x < -1e9 || p.y > 1e9 || p.y < -1e9) {
			std::cout << "impossible" << '\n';
			return 0;
		}
		a2[i].first = std::round(p.x);
		a2[i].second = std::round(p.y);
		if (std::abs(ld(a2[i].first) - p.x) > EPS) {
			std::cout << "impossible" << '\n';
			return 0;
		}
		if (std::abs(ld(a2[i].second) - p.y) > EPS) {
			std::cout << "impossible" << '\n';
			return 0;
		}
	}
	std::sort(b.begin(), b.end());
	std::sort(a2.begin(), a2.end());
	if (a2 != b) {
		std::cout << "impossible" << '\n';
		return 0;
	}

	std::cout << "possible" << '\n';

	return 0;
}
