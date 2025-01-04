#include <algorithm>
#include <cassert>
#include <cstdint>
#include <iostream>
#include <numeric>
#include <vector>
#include <array>
#include <tuple>

using namespace std;

#define all(a) (a).begin(), (a).end()

using u64 = uint64_t;
using i64 = int64_t;

using int128_t = __int128_t;
struct frac {
	i64 n, d;
	void red() {
		if (d == 1) return;
		i64 g = gcd(n, d);
		n /= g, d /= g;
		if (d < 0) n = -n, d = -d;
	}
	explicit frac(i64 n = 0) : n(n), d(1) { }
	frac(i64 n, i64 d) : n(n), d(d) { red(); }
	frac& operator+=(const frac& rhs) {
		n = rhs.d * n + rhs.n * d;
		d *= rhs.d;
		red();
		return *this;
	}
	frac operator+(const frac& rhs) const {
		frac res = *this;
		return res += rhs;
	}
	frac& operator-=(const frac& rhs) {
		n = rhs.d * n - rhs.n * d;
		d *= rhs.d;
		red();
		return *this;
	}
	frac operator-(const frac& rhs) const {
		frac res = *this;
		return res -= rhs;
	}
	frac& operator*=(const frac& rhs) {
		n *= rhs.n, d *= rhs.d;
		red();
		return *this;
	}
	frac operator*(const frac& rhs) const {
		frac res = *this;
		return res *= rhs;
	}
	frac operator-() const {
		return frac(-n, d);
	}
	bool operator<(const frac& rhs) const {
		return n * rhs.d < rhs.n * d;
	}
	bool operator==(const frac& rhs) const {
		return tie(n, d) == tie(rhs.n, rhs.d);
	}
	explicit operator double() const {
		return n / (double)d;
	}
};
ostream& operator<<(ostream& out, const frac& f) {
	out << f.n;
	if (f.d != 1) out << "/" << f.d;
	return out;
}

template <typename T>
struct pt_t {
	T x, y;
	pt_t() : x(T {}), y(T {}) { }
	pt_t(T x, T y) : x(x), y(y) { }
	pt_t operator-(const pt_t& rhs) const {
		return pt_t(x - rhs.x, y - rhs.y);
	}
	pt_t operator+(const pt_t& rhs) const {
		return pt_t(x + rhs.x, y + rhs.y);
	}
	T operator*(const pt_t& rhs) const {
		return x * rhs.x + y * rhs.y;
	}
	pt_t operator*(const T& rhs) const {
		return pt_t(x * rhs, y * rhs);
	}
	T operator^(const pt_t& rhs) const {
		return x * rhs.y - y * rhs.x;
	}
	bool operator<(const pt_t& rhs) const {
		return tie(x, y) < tie(rhs.x, rhs.y);
	}
	bool operator==(const pt_t& rhs) const {
		return tie(x, y) == tie(rhs.x, rhs.y);
	}
	bool operator!=(const pt_t& rhs) const {
		return not (*this == rhs);
	}
	pt_t& operator/=(i64 rhs) {
		static_assert(std::is_same_v<T, frac>);
		x *= frac(1, rhs), y *= frac(1, rhs);
		return *this;
	}
	pt_t operator/(i64 rhs) {
		auto res = *this;
		res /= rhs;
		return res;
	}
	template<typename T2 = T>
	enable_if_t<is_same_v<T2, i64>, int128_t> dist2() const {
		return x * (int128_t)x + y * (int128_t)y;
	}
	template<typename T2 = T>
	enable_if_t<is_same_v<T2, i64>, pt_t<frac>> tf() const {
		return pt_t<frac>(frac(x), frac(y));
	}
};
using fpt = pt_t<frac>;
using pt = pt_t<i64>;

// 1=ccw, 0=straight, -1=cw
template <typename ptA, typename ptB, typename ptC>
int ccw(const ptA& p0, const ptB& p1, const ptC& p2) {
	using T = conditional_t<is_same_v<fpt, ptA>, frac, i64>;
	// const auto r = (p1 - p0) ^ (p2 - p0);
	// return r > 0 ? 1 : r < 0 ? -1 : 0;
	const auto d1 = (T { p1.x } - p0.x) * (T { p2.y } - p0.y);
	const auto d2 = (T { p2.x } - p0.x) * (T { p1.y } - p0.y);
	return (T { 0 } < d1 - d2) - (T { 0 } < d2 - d1);
}
template <typename T>
std::ostream& operator<<(std::ostream& out, const pt_t<T>& p) {
	return out << '(' << p.x << ", " << p.y << ')';
}

i64 twoarea(const vector<pt>& poly) {
	i64 res = 0;
	for (u64 j = poly.size() - 1, i = 0; i < poly.size(); j = i++)
		res += (poly[j].x - poly[i].x) * (poly[i].y + poly[j].y);
	return res;
}

fpt centroid(const vector<pt>& poly) {
	// https://www.spatialanalysisonline.com/HTML/centroids_and_centers.htm
	i64 x = 0, y = 0;
	for (u64 j = poly.size() - 1, i = 0; i < poly.size(); j = i++) {
		const auto f = (poly[j].x * poly[i].y - poly[i].x * poly[j].y);
		x += f * (poly[j].x + poly[i].x);
		y += f * (poly[j].y + poly[i].y);
	}
	const auto tarea = 3 * twoarea(poly); // 6 * area
	return fpt(frac(x, tarea), frac(y, tarea));
}

int main() {
	cin.tie(nullptr), ios::sync_with_stdio(false);

	u64 n;
	cin >> n;
	const auto clamp = [&](u64 i) { return i>=n ? i-=n : i; };
	vector<pt> poly(n);
	for (u64 i = 0; i < n; i++)
		cin >> poly[i].x >> poly[i].y;
	assert(twoarea(poly) > 0); // counterclockwise
	const auto c = centroid(poly);
	{ // collapse line segments that are colinear with the centroid
		vector<pt> npoly;
		for (u64 k = 0, i = 0; k < n; k++, i++) {
			npoly.emplace_back(poly[i]);
			if (ccw(c, poly[i], poly[clamp(i+1)]) == 0)
				i++, k++;
		}
		if (ccw(c, npoly.back(), npoly[0]) == 0) npoly.pop_back();
		poly = npoly;
		n = poly.size();
	}
	vector<u64> order(n);
	iota(all(order), 0);
	sort(all(order), [&](u64 li, u64 ri) {
		const auto &l = poly[li], r = poly[ri];
		// TODO: can be simplified a lot
		fpt ll = l.tf() - c, rr = r.tf() - c;
		bool bl = ll < fpt(), br = rr < fpt();
		if (bl) ll = fpt(-ll.x, -ll.y);
		if (br) rr = fpt(-rr.x, -rr.y);
		return (ll ^ rr).n > 0;
	});

	vector<bool> concave(n);
	// 0b01 set iff (i+1) is in ccw direction, 0b10 set iff (i-1) is in ccw
	vector<uint8_t> type(n);
	for (u64 i = 0, j = 1, k = 2, l = 0; l < n; i = j, j = k, k = clamp(k + 1), l++) {
		concave[j] = ccw(poly[i], poly[j], poly[k]) < 0;
		if (ccw(c, poly[i], poly[j]) > 0) type[i] |= 1;
		else type[j] |= 2;
	}

	vector<bool> cur_open(n);
	u64 num_open = 0;
	const auto open = [&](u64 i) {
		assert(not cur_open[i]);
		num_open++, cur_open[i] = true;
	};
	const auto close = [&](u64 i) {
		num_open -= cur_open[i];
		cur_open[i] = false;
	};
	// edge i-(i+1) is indexed by i
	pt last;
	for (u64 r = 0, ii = 0; r < 3 * n; ) {
		const auto i = order[ii];
		array<vector<u64>, 4> pts;
		if (r >= 2*n and num_open == 2) {
			fpt real_last = last.tf();
			if ((real_last - c) * (poly[i].tf() - c) < frac(0))
				real_last = c - (real_last - c);
			fpt res = real_last + poly[i].tf();
			res.x *= frac(1,2), res.y *= frac(1,2);
			cout << c.x << ' ' << c.y << ' ' << res.x << ' ' << res.y << '\n';
			return 0;
		}
		bool impossible = false;
		for ( ; ccw(c, poly[i], poly[order[ii]]) == 0; ii = clamp(ii + 1), r++) {
			last = poly[order[ii]];
			pts[type[order[ii]]].emplace_back(order[ii]);
			if (__builtin_popcount(type[order[ii]]) % 2 == 0 and concave[order[ii]])
				impossible = true;
		}

		for (u64 t = 0; t < 4; t++) {
			for (u64 i : pts[t]) {
				const auto pre = (i == 0 ? n : i) - 1;

				if (t & 2) open(pre);
				else close(pre);

				if (t & 1) open(i);
				else close(i);
			}

			if (not impossible and t == 2 and r >= n) {
				assert(num_open >= 2);
				if (num_open == 2) {
					cout << c.x << ' ' << c.y << ' ' << poly[i].x << ' ' << poly[i].y << '\n';
					return 0;
				}
			}
		}
	}

	cout << "impossible\n";

	return 0;
}
