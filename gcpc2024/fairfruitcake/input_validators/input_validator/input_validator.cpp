#include "validation.h"

#define main sol_main
#include "solution.hpp"
#undef main

constexpr size_t MAX_N = 1e5;
constexpr long long MAX_COORD = 1e6;

struct seg {
	pt l, r;
	seg(pt l, pt r) : l(l), r(r) {}
	bool operator==(const seg& rhs) const { return l==rhs.l && r==rhs.r; }
};
std::ostream& operator<<(std::ostream& out, const seg& p) {
	return out << p.l << '-' << p.r;
}
i64 lt_at(const seg& lhs, const seg& rhs, i64 x) {
	const i64 d1 = lhs.r.x - lhs.l.x;
	const i64 n1 = d1 * lhs.l.y + (lhs.r.y - lhs.l.y) * (x - lhs.l.x);
	const i64 d2 = rhs.r.x - rhs.l.x;
	const i64 n2 = d2 * rhs.l.y + (rhs.r.y - rhs.l.y) * (x - rhs.l.x);
	return n1 * d2 - n2 * d1; //n1 / d1 < n2 / d2;
}
bool operator<(const seg& lhs, const seg& rhs) {
	if (lhs == rhs) return false;
	if (auto y = lhs.l.y; lhs.r.y == y && rhs.l.y == y && rhs.r.y == y)
		return std::tie(lhs.l.x, lhs.r.x) > std::tie(rhs.l.x, rhs.r.x);
	for (i64 x = std::max(lhs.l.x, rhs.l.x); ; x++) {
		if (auto r = lt_at(lhs, rhs, x); r != 0) {
			return r < 0;
		}
	}
}
// strict
bool point_on_seg(const seg& b, const pt& p) {
	if (ccw(b.l, b.r, p)) return false;
	const i64 cx = (p.x-b.l.x)*(p.x-b.r.x);
	const i64 cy = (p.y-b.l.y)*(p.y-b.r.y);
	return (cx < 0 || cy < 0);
}
// true iff intersection is not on endvertex for at least one seg
bool intersects(const seg& a, const seg& b) {
	if (point_on_seg(a, b.l) || point_on_seg(a, b.r) ||
			point_on_seg(b, a.l) || point_on_seg(b, a.r))
		return true;
	int ab = ccw(a.l, a.r, b.l) * ccw(a.l, a.r, b.r);
	int ba = ccw(b.l, b.r, a.l) * ccw(b.l, b.r, a.r); 
	return ab < 0 && ba < 0;
}

void is_simple(const std::vector<pt>& p, InputValidator& v) {
	const size_t n = p.size();
	std::vector<size_t> ord;
	for (size_t i = 0; i < n; i++)
		ord.emplace_back(i);
	std::sort(ord.begin(), ord.end(), [&](size_t i, size_t j) { return p[i] < p[j]; });
	std::multiset<seg> cur;
	std::map<i64, std::vector<seg>> rm;

	for (size_t ii = 0; ii < ord.size(); ) {
		const auto x = p[ord[ii]].x;
		const size_t j = [&] {
			size_t j = ii+1;
			for ( ; j < ord.size() && x == p[ord[j]].x; j++);
			return j;
		}();

		while (rm.begin() != rm.end() && rm.begin()->first < x) {
			for (const auto& s : rm.begin()->second)
				cur.erase(s);
			rm.erase(rm.begin());
		}

		std::vector<size_t> intervals; // smaller index
		std::vector<seg> add;
		for (size_t i = ii; i < j; i++) {
		    v.check(i <= ii or p[ord[i]] != p[ord[i-1]],
					"point ", p[ord[i]], " occurs (at least) twice: @", ord[i]
					," and @", ord[i-1]);
			for (i64 k = -1; k <= 1; k+=2) {
				const size_t ni = (ord[i] + k + n) % n;
				if (x == p[ni].x && k == 1)
					intervals.emplace_back(ord[i]);
				else if (p[ni].x > x)
					add.emplace_back(p[ord[i]], p[ni]);
				else if (p[ni].x < x) {} // non-vertical seg ending here
			}
		}
		const auto get_seg = [&](size_t i) {
			auto a = p[i], b = p[(i+1)%n];
			if (b < a) std::swap(a,b);
			return seg(a,b);
		};
		std::sort(intervals.begin(), intervals.end(), [&](size_t a, size_t b) {
			return get_seg(a).l < get_seg(b).l;
		});
		for (size_t i = 0; i < intervals.size(); i++) {
			const auto[l,r] = [&] {
				auto s = get_seg(intervals[i]);
				return std::make_pair(s.l.y, s.r.y);
			}();
			const seg low(pt(x, l), pt(x+1, l));
			const seg high(pt(x, r), pt(x+1, r));
			auto lo = cur.lower_bound(low);
			while (lo != cur.end() and (lt_at(*lo, high, x) <= 0 or lo->r.x < x)) {
				assert(lt_at(low, *lo, x) <= 0);
				v.check(lo->r == pt(x,l) or lo->r == pt(x,r) or lo->r.x < x,
						"segment ", *lo, " intersects vertical seg. at x=", x,
						' ', l, '-', r);
				lo = cur.erase(lo);
			}

			v.check(i == 0 or get_seg(intervals[i-1]).r.y < l,
					"vertical segments intersect at x=", x, ": ",
					get_seg(intervals[i]), " , ", get_seg(intervals[i-1]));
		}
		if (rm.begin() != rm.end() && rm.begin()->first == x) {
			for (const auto& s : rm.begin()->second)
				cur.erase(s);
			rm.erase(rm.begin());
		}
		for (const auto& s : add) {
			auto it = cur.emplace(s);
			while (it != cur.begin() && std::prev(it)->r.x < x)
				it = cur.erase(std::prev(it));
			assert(*it == s);
			v.check(it == cur.begin() or not intersects(*std::prev(it), *it),
				"segments intersect: ", *std::prev(it), " & ", *it);
			it++;
			while (it != cur.end() && it->r.x < x)
				it = cur.erase(it);
			assert(*std::prev(it) == s);
			v.check(it == cur.end() or not intersects(*it, *std::prev(it)),
					"segments intersect: ", *std::prev(it), " & ", *it);
			rm[s.r.x].emplace_back(s);
		}
		ii = j;
	}
}

int main(int argc, char *argv[]) {
	InputValidator v(argc, argv);
	size_t n = v.read_integer("n", 1, MAX_N);
	v.newline();
	std::vector<pt> poly(n);
	for (size_t i = 0; i < n; i++) {
		poly[i].x = v.read_integer("x_" + std::to_string(i), 0, MAX_COORD);
		v.space();
		poly[i].y = v.read_integer("y_" + std::to_string(i), 0, MAX_COORD);
		v.newline();
	}

	v.check(twoarea(poly) > 0, " polygon not counterclockwise");
	// check point-symmetry
	v.check(n % 2 == 0, " n must be even");
	const pt twocenter = poly[n / 2] + poly[0];
	for (size_t i = 1; i < n / 2; i++) {
		auto tmp = poly[n/2+i] + poly[i];
		v.check(twocenter == tmp,
			"not point-symmetric, expected center at ",
			twocenter.x / 2.0, ",", twocenter.y / 2.0,
			" but at ", i, ' ', i+n/2, " we find ",
			tmp.x / 2.0, ",", tmp.y / 2.0 );
	}
	for (size_t i = 0; i < n; i++)
		v.check(ccw(poly[i], poly[(i+1)%n], poly[(i+2)%n]) != 0,
			"three consecutive colinear points @ ", i, ": ",
			poly[i], ", ", poly[(i+1)%n], ", ", poly[(i+2)%n]);
	is_simple(poly, v);
	v.eof_and_AC();
}
