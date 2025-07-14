#include "validate.h"
#include <cassert>

using namespace std;
using i64 = int64_t;
#define sz(a) ((i64)(a).size())
#define all(a) (a).begin(),(a).end()

struct pt{
	i64 x,y;
	pt():x(0),y(0){};
	pt(i64 x,i64 y):x(x),y(y){};
	pt operator+(const pt& p) const { return pt(x+p.x,y+p.y);}
	pt operator-(const pt& p) const { return pt(x-p.x,y-p.y);}
	auto operator<(const pt& p) const { return (x == p.x) ? y < p.y : x < p.x; }
	auto operator>(const pt& p) const { return (x == p.x) ? y > p.y : x > p.x; }
	auto operator==(const pt& p) const { return x == p.x && y == p.y; }
};

i64 two_area(const std::vector<pt>& poly) {
	i64 res = 0;
	for (i64 j = poly.size() - 1, i = 0; i < poly.size(); j = i++)
		res += (poly[i].x - poly[j].x) * (poly[i].y + poly[j].y);
	return res;
}

std::ostream& operator<<(std::ostream& out, const pt& p) {
	return out << '<' << p.x << ", " << p.y << '>';
}

// ccw test. decides whether three points are arranged counterclockwise. 1=ccw, 0=straight, -1=cw
int ccw(pt p0, pt p1, pt p2) {
	const i64 d1 =(p1.x-p0.x)*(p2.y-p0.y);
	const i64 d2 =(p2.x-p0.x)*(p1.y-p0.y);
	return (d1-d2>0)-(d2-d1>0);
}

bool intersect(std::vector<pt> poly, bool flipped = false) {
	using namespace std;
	using namespace InputValidator;

	vector<pair<i64,pt>> horizontal; // (x, (x_end,y))
	vector<pair<pt, i64>> vertical; // ((x, y_lo), y_hi)
	for (size_t j = poly.size() - 1, i = 0; i < poly.size(); j = i++)
		if (poly[i].y == poly[j].y) {
			auto xl = poly[i].x, xr = poly[j].x;
			if (xr < xl) swap(xl, xr);
			horizontal.emplace_back(xl, pt(xr, poly[i].y));
		} else { assert(poly[i].x == poly[j].x);
			auto yl = poly[i].y, yr = poly[j].y;
			if (yr < yl) swap(yr, yl);
			vertical.emplace_back(pt(poly[i].x, yl), yr);
		}

	sort(horizontal.begin(), horizontal.end());
	sort(vertical.begin(), vertical.end());

	map<i64, pair<i64, i64>> cur; // y -> (x_hi, x_lo)

	for (size_t ii = 0, vii = 0; ii < horizontal.size(); ) {
		const auto x = horizontal[ii].first;

		size_t j = ii+1;
		while (j < horizontal.size() && horizontal[j].first == x) j++;

		for (size_t i = ii; i < j; i++) {
			auto[xr, y] = horizontal[i].second;
			auto[it,succ] = cur.emplace(y, make_pair(x, xr));
			if (!succ) {
				if (it->second.second >= x)
					return juryOut << (flipped?"FLIPPED: ":"")
						<< "two horizontal segments touch!? @ y = " << y << "   "
						<< it->second.first << "-" << it->second.second << "  vs. "
						<< x << "-" << xr << WA, true;
				else
					it->second = make_pair(x, xr);
			}
		}

		auto last_vii = vertical.size();

		// check vertical
		for ( ; vii < vertical.size() && vertical[vii].first.x <= x; vii++) {
			const auto vx = vertical[vii].first.x;
			const auto ly = vertical[vii].first.y, hy = vertical[vii].second;
			auto it = cur.lower_bound(ly);
			while (it != cur.end() && it->first <= hy) {
				if (it->second.second < vx) { it = cur.erase(it); continue; }
				if (it->second.first == x) { it++; continue; }
				// intersection
				if (it->second.second == vx && (it->first == ly || it->first == hy)) {
					// intersection on endpoint
					it++;
				} else {
					// ''true`` intersection
					return juryOut << (flipped?"FLIPPED: ":"") << "intersection @ " <<
						pt(vx, it->first) << " with vertical segment " << ly << "-" << hy
						<< " and horizontal segment ending at " << it->second << WA, true;
				}
			}

			if (vertical[vii].first.x == x) {
				if (vii > last_vii && vertical[last_vii].second >= vertical[vii].first.y) {
					return juryOut << (flipped?"FLIPPED: ":"")
						<< "two vertical segments touch?! @ x = " << x << "  y: "
						<< vertical[last_vii].first.y << "-" << vertical[last_vii].second << ", "
						<< vertical[vii].first.y << "-" << vertical[vii].second << WA, true;
				}
				last_vii = vii;
			}
		}

		ii = j;
	}

	if (!flipped) {
		for (auto&[x,y] : poly)
			swap(x,y);
		return intersect(poly, true);
	}
	return false;
}

vector<pt> read_poly(i64 n, InputStream& in)
{
	vector<pt> poly(n);
	for (auto& [x,y] : poly) {
		x = in.integer(1, 1'000'000'001);
		in.space();
		y = in.integer(1, 1'000'000'001);
		in.newline();
	}
	return poly;
}

void check_poly(const vector<pt>& poly, OutputStream& juryOut)
{
	using namespace Verdicts;

	const auto n = sz(poly);

	if (std::set<pt> pts(poly.begin(), poly.end()); sz(pts) != n)
		juryOut << "polygon contains duplicate vertices!" << WA;

	if (two_area(poly) > 0)
		juryOut << "polygon vertices are not given in counterclockwise order" << WA;

	for (i64 i = 0; i < n; i++) {
		if (poly[i] == poly[(i+1)%n])
			juryOut << "consecutive points are equal, i=" << i << " : " << poly[i] << WA;
		const auto c = ccw(poly[i], poly[(i+1)%n], poly[(i+2)%n]);
		if (c == 0)
			juryOut << "points are colinear, i=" << i << " : "
				<< poly[i] << ' '
				<< poly[(i+1)%n] << ' '
				<< poly[(i+2)%n]
				<< WA;
		if ((poly[i].x == poly[(i+1)%n].x) ==
				(poly[i].y == poly[(i+1)%n].y))
			juryOut << "polygon is not rectilinear, i=" << i << " : "
				<< poly[i] << ' '
				<< poly[(i+1)%n]
				<< WA;
	}

	if (intersect(poly))
		juryOut << "polygon is self-intersecting" << WA;
}

int main(int argc, char **argv) {
	using namespace InputValidator;
	init(argc, argv);

	const i64 n = testIn.integer(4, 100'001);
	testIn.newline();

	const auto poly = read_poly(n, testIn);
	check_poly(poly, juryOut);

	testIn.eof();

	return AC;
}
