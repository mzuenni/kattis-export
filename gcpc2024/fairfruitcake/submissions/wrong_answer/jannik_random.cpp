#include <cassert>
#include <algorithm>
#include <cassert>
#include <cstdint>
#include <iostream>
#include <numeric>
#include <random>
#include <vector>
#include <chrono>
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
	template<typename T2 = T>
	enable_if_t<is_same_v<T2, i64>, int128_t> dist2() const {
		return x * (int128_t)x + y * (int128_t)y;
	}
	template<typename T2 = T>
	enable_if_t<is_same_v<T2, i64>, pt_t<frac>> tf() const {
		return pt_t<frac>(frac(x), frac(y));
	}
	template<typename T2 = T>
	enable_if_t<is_same_v<T2, i64>, pt_t<i64>> operator/(i64 rhs) {
		return pt_t(x / rhs, y / rhs);
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

bool test(vector<pt> poly, const pt& a, const pt& b) {
	if (a == b) return false;

	u64 n = poly.size();
	const auto clamp = [&](u64 i) { return i>=n ? i-=n : i; };

	for (u64 i = 0, j = 1, k = 2; i < j; i = j, j = k, k = clamp(k + 1)) {
		if (ccw(poly[i], poly[j], poly[k]) < 0
		    and ccw(a, b, poly[j]) == 0
		    and ccw(a, b, poly[i]) == ccw(a, b, poly[k]))
			return false;
	}

	// remove all points on a-b
	poly.erase(remove_if(
	                poly.begin(),
	                poly.end(),
	                [&](const pt& p) { return ccw(a, b, p) == 0; }),
	    poly.end());
	n = poly.size();

	size_t hits = 0;
	for (u64 i = 0, j = 1; j < n; i = j++)
		if (ccw(a, b, poly[i]) != ccw(a, b, poly[j]))
			hits++;
	if (ccw(a, b, poly.back()) != ccw(a, b, poly[0]))
		hits++;
	assert(hits >= 2);

	return hits <= 2;
}

int main() {
	auto start = chrono::steady_clock::now();

	u64 n;
	cin >> n;
	const auto clamp = [&](u64 i) { return i>=n ? i-=n : i; };

	vector<pt> poly(n);
	for (auto&[x,y] : poly) {
		cin >> x >> y;
		x *= 2, y *= 2;
	}

	const pt c = (poly[0] + poly[n / 2]) / 2;
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
		const pt &l = poly[li], r = poly[ri];
		pt ll = l - c, rr = r - c;
		bool bl = ll < pt(), br = rr < pt();
		if (bl) ll = pt(-ll.x, -ll.y);
		if (br) rr = pt(-rr.x, -rr.y);
		return (ll ^ rr) > 0;
	});

	vector<pt> angles;
	for (u64 i = 0; i < n; ) {
		pt p = poly[order[i++]];
		if (p < c) p = c + c - p;
		assert(not (p < c));
		while (i < n and ccw(c, p, poly[order[i]]) == 0)
			i++;
		if (i == n and ccw(c, p, poly[order[0]]) == 0)
			continue;
		angles.emplace_back(p);
	}

	mt19937 gen(random_device{}());
	uniform_int_distribution<> distr(0, angles.size() - 1);

	const auto print = [&](const pt& b) {
		cout << c.x << "/2 " << c.y << "/2 " << b.x << "/2 " << b.y << "/2\n";
		exit(0);
	};

	if (auto x = c + pt(2,0); test(poly, c, x))
		print(x);
	if (auto x = c + pt(0,2); test(poly, c, x))
		print(x);
	
	while (chrono::duration_cast<chrono::milliseconds>(chrono::steady_clock::now() - start).count() < 2900) {
		const auto i = distr(gen);
		if (test(poly, c, angles[i]))
			print(angles[i]);
		if (pt x = (angles[i] + angles[(i+1)%angles.size()]) / 2; test(poly, c, x))
			print(x);
	}
	cout << "impossible\n";
}
