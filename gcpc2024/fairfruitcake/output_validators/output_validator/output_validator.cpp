#include <iostream>
#include <algorithm>
using i128 = __int128_t;
std::ostream& operator<<(std::ostream& out, i128 v) {
	if (v < 0) return out << '-' << -v;
	if (v == 0) return out << '0';
	std::string s;
	for (; v > 0; v /= 10) s.push_back('0' + v%10);
	std::reverse(s.begin(), s.end());
	return out << s;
}
#include "validate.h"
auto parse(const std::string& s) -> i128 {
	i128 res = {};
	if (!details::parse<i128>(s, res)) {
		ValidateBase::juryOut << "Could not parse i64 \"" << s << "\"!" << WA;
	}
	if (abs(res) > 1'000'000'000) {
		ValidateBase::juryOut << "Could not parse i64 \"" << s << "\"!" << WA;
	}
	return res;
}
std::istream& operator>>(std::istream& in, i128& v) {
	std::string s;
	in >> s;
	v = parse(s);
	return in;
}
#include <cassert>
#define int64_t i128
#define main sol_main
#include "solution.hpp"
#undef main
static_assert(std::is_same_v<i64, i128>);
auto parse_frac(const string& s) -> frac {
	size_t p = s.find('/');
	i64 n, d = 1;
	n = parse(s.substr(0, p));
	if (p < s.size())
		d = parse(s.substr(p + 1));
	if (d == 0) 
		OutputValidator::juryOut << "fraction has 0 denominator" << WA;
	return frac(n, d);
}

int main(int argc, char** argv) {
	OutputValidator::init(argc, argv);

	using namespace OutputValidator;

	
	u64 n = testIn.integer();
	const auto clamp = [&](u64 i) { return i>=n ? i-=n : i; };

	vector<pt> poly(n);
	for (auto&[x,y] : poly) {
		x = testIn.integer();
		y = testIn.integer();
	}
	const bool impossible = stringEqual(juryAns.string(), "impossible", false);

	auto x0 = teamAns.string();
	if (stringEqual(x0, "impossible")) {
		if (impossible)
			juryOut << "OK, impossible" << AC;
		else
			juryOut << "team says impossible, but jury has answer" << WA;
	}

	fpt a, b;
	a.x = parse_frac(x0), teamAns.space();
	a.y = parse_frac(teamAns.string()), teamAns.space();
	b.x = parse_frac(teamAns.string()), teamAns.space();
	b.y = parse_frac(teamAns.string()), teamAns.newline();
	teamAns.eof();

	if (a == b)
		juryOut << "team printed the same point twice" << WA;

	// check that a-b intersects the centroid
	fpt center = fpt(frac(poly[0].x + poly[n/2].x, 2), frac(poly[0].y + poly[n/2].y, 2));
	if (ccw(a, b, center) != 0)
		juryOut << "line does not cut polygon into two equal halves" << WA;

	{ // collapse line segments that are colinear with the centroid
		vector<pt> npoly;
		for (u64 k = 0, i = 0; k < n; k++, i++) {
			npoly.emplace_back(poly[i]);
			if (ccw(center, poly[i], poly[clamp(i+1)]) == 0)
				i++, k++;
		}
		if (ccw(center, npoly.back(), npoly[0]) == 0) npoly.pop_back();
		poly = npoly;
		n = poly.size();
	}


	for (u64 i = 0, j = 1, k = 2; i < j; i = j, j = k, k = clamp(k + 1)) {
		if (ccw(poly[i], poly[j], poly[k]) < 0
		    and ccw(a, b, poly[j]) == 0
		    and ccw(a, b, poly[i]) == ccw(a, b, poly[k]))
			// poly[j] is concave and 
			// TODO: remove possible information leak
			juryOut << "line splits polygon into more than two pieces" << WA;// @ " << poly[j].x << ',' << poly[j].y << WA;
	}

	// remove all points on a-b
	poly.erase(remove_if(
	                poly.begin(),
	                poly.end(),
	                [&](const pt& p) { return ccw(a, b, p) == 0; }),
	    poly.end());
	n = poly.size();

	size_t hits = 0;
	for (u64 i = 0, j = 1, k = 2; i < j; i = j, j = k, k = clamp(k + 1)) {
		if (ccw(a, b, poly[i]) * ccw(a, b, poly[j]) < 0)
			hits++;
	}
	if (hits > 2)
		juryOut << "line cuts polygon into more than two pieces" << WA;

	if (impossible)
		juryOut << "impossible! team found solution but jury didn't" << FAIL;

	juryOut << "OK" << AC;
}
