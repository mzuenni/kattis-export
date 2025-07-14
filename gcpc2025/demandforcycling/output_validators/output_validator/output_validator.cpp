#include "validate.h"
#include <cassert>

using namespace std;
using i64 = int64_t;
#define sz(a) ((i64)(a).size())
#define all(a) (a).begin(), (a).end()

struct pt {
	i64 x, y;
	pt()
		: x(0)
		, y(0) { };
	pt(i64 x, i64 y)
		: x(x)
		, y(y) { };
	pt operator+(const pt& p) const { return pt(x + p.x, y + p.y); }
	pt operator-(const pt& p) const { return pt(x - p.x, y - p.y); }
	auto operator<(const pt& p) const { return (x == p.x) ? y < p.y : x < p.x; }
	auto operator>(const pt& p) const { return (x == p.x) ? y > p.y : x > p.x; }
};

ostream& operator<<(ostream& out, const pt& p)
{
	return out << '<' << p.x << ',' << p.y << '>';
}

vector<pt> read_poly(InputStream& in, Integer max_n)
{
	Integer n = in.integer(4, max_n + 1);
	in.newline();
	vector<pt> poly(n);
	for (auto& [x, y] : poly) {
		x = in.integer(1, 1'000'000'001);
		in.space();
		y = in.integer(1, 1'000'000'001);
		in.newline();
	}
	return poly;
}

i64 two_area(const std::vector<pt>& poly)
{
	i64 res = 0;
	for (i64 j = sz(poly) - 1, i = 0; i < sz(poly); j = i++)
		res += (poly[i].x - poly[j].x) * (poly[i].y + poly[j].y);
	return res;
}

// ccw test. decides whether three points are arranged counterclockwise. 1=ccw, 0=straight, -1=cw
int ccw(pt p0, pt p1, pt p2)
{
	const i64 d1 = (p1.x - p0.x) * (p2.y - p0.y);
	const i64 d2 = (p2.x - p0.x) * (p1.y - p0.y);
	return (d1 - d2 > 0) - (d2 - d1 > 0);
}

void check_poly(const vector<pt>& poly, OutputStream& juryOut, const Verdicts::Verdict verdict)
{
	using namespace Verdicts;

	const auto n = sz(poly);

	if (std::set<pt> pts(poly.begin(), poly.end()); sz(pts) != n)
		juryOut << "duplicate vertices!" << verdict;

	if (two_area(poly) > 0)
		juryOut << "vertices are not given in counterclockwise order" << verdict;

	for (i64 i = 0; i < n; i++) {
		const auto c = ccw(poly[i], poly[(i + 1) % n], poly[(i + 2) % n]);
		if (c == 0)
			juryOut << "points are collinear, i=" << i << " : "
					<< poly[i] << ' '
					<< poly[(i + 1) % n] << ' '
					<< poly[(i + 2) % n]
					<< verdict;
		if ((poly[i].x == poly[(i + 1) % n].x) == (poly[i].y == poly[(i + 1) % n].y))
			juryOut << "polygon is not rectilinear, i=" << i << " : "
					<< poly[i] << ' '
					<< poly[(i + 1) % n]
					<< verdict;
	}
}

Integer circumference(const vector<pt>& poly)
{
	const Integer n = poly.size();
	Integer res = 0;
	for (Integer j = n - 1, i = 0; i < n; j = i++)
		res += abs(poly[i].x - poly[j].x) + abs(poly[i].y - poly[j].y);
	return res;
}

bool rectilinear_convex(const vector<pt>& poly)
{
	const Integer n = poly.size();
	// rectilinear convex iff there are no two consecutive convex (i.e. CW) vertices
	for (Integer i = 0; i < n; i++) {
		const auto a = ccw(poly[i], poly[(i + 1) % n], poly[(i + 2) % n]);
		const auto b = ccw(poly[(i + 1) % n], poly[(i + 2) % n], poly[(i + 3) % n]);
		if (a < 0 and b < 0)
			return false;
	}
	return true;
}

// NOTE: this assumes that the outer polygon is rectilinear convex
bool contains(const vector<pt>& inner, const vector<pt>& outer)
{
	const auto n = inner.size();
	// we can split the rectilinear convex team-polygon into an upper and a lower polyline (which never intersect)
	i64 min_x = 0, max_x = 0;
	for (i64 i = 0; i < sz(outer); i++) {
		if (outer[i] < outer[min_x])
			min_x = i;
		if (outer[i] > outer[max_x])
			max_x = i;
	}
	map<i64, i64> low, high;
	for (i64 i = min_x; i != max_x; i = (i + 2) % sz(outer))
		low.emplace(outer[i].x, outer[i].y);
	for (i64 i = (max_x + 1) % sz(outer); i != (min_x + 1) % sz(outer); i = (i + 2) % sz(outer))
		high.emplace(outer[i].x, outer[i].y);

	i64 offset = (inner[0].y != inner[1].y);
	for (i64 ii = 0; ii < n; ii += 2) {
		auto a = inner[(ii + offset) % n], b = inner[(ii + offset + 1) % n];
		assert(a.y == b.y);
		if (b.x < a.x)
			swap(a, b);
		if (a.x < outer[min_x].x or b.x > outer[max_x].x)
			return false;

		auto it = low.upper_bound(a.x);
		assert(it != low.begin()); // we have a.x >= low.begin()->x
		for (--it; it != low.end() and it->first < b.x; it++)
			if (it->second > a.y)
				return false;
		it = high.upper_bound(a.x);
		assert(it != high.begin());
		for (--it; it != high.end() and it->first < b.x; it++)
			if (it->second < a.y)
				return false;
	}
	return true;
}

int main(int argc, char** argv)
{
	using namespace OutputValidator;
	init(argc, argv);

	const auto poly = read_poly(testIn, 100'001);
	const Integer n = poly.size();

	const auto jury_poly = read_poly(juryAns, n + 1);
	// const Integer jury_n = jury_poly.size();
	juryAns.eof();

	check_poly(jury_poly, juryOut, FAIL);
	if (not rectilinear_convex(jury_poly))
		juryOut << "jury answer is not rectilinear convex!" << FAIL;
	if (not contains(poly, jury_poly))
		juryOut << "jury answer is invalid!" << FAIL;

	const auto team_poly = read_poly(teamAns, n + 1);
	teamAns.eof();
	const Integer team_n = team_poly.size();

	check_poly(team_poly, juryOut, WA);

	// team poly must be rectilinear convex, otherwise it cannot be optimal
	// => if team poly has optimal circumference and is not rectilinear convex, it cannot contain poly
	if (circumference(team_poly) > circumference(jury_poly))
		juryOut << "team polygon has circumference of " << circumference(team_poly) << ", but jury has " << circumference(jury_poly) << WA;
	if (not rectilinear_convex(team_poly))
		juryOut << "team polygon does not completely contain input polygon" << WA;

	if (circumference(team_poly) > circumference(jury_poly))
		juryOut << "team polygon has circumference of " << circumference(team_poly) << ", but jury has " << circumference(jury_poly) << WA;
	if (not contains(poly, team_poly))
		juryOut << "team polygon does not contain input polygon" << WA;
	if (circumference(team_poly) < circumference(jury_poly))
		juryOut << "team polygon has circumference of " << circumference(team_poly) << ", but jury has " << circumference(jury_poly) << FAIL;
	juryOut << "OK" << AC;
}
