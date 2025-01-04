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

struct pt {
	i64 x, y;
	pt() : x(0), y(0) { }
	pt(i64 x, i64 y) : x(x), y(y) { }
	pt operator-(const pt& rhs) const {
		return pt(x - rhs.x, y - rhs.y);
	}
	pt operator+(const pt& rhs) const {
		return pt(x + rhs.x, y + rhs.y);
	}
	i64 operator*(const pt& rhs) const {
		return x * rhs.x + y * rhs.y;
	}
	i64 operator^(const pt& rhs) const {
		return x * rhs.y - y * rhs.x;
	}
	bool operator<(const pt& rhs) const {
		return tie(x, y) < tie(rhs.x, rhs.y);
	}
	bool operator==(const pt& rhs) const {
		return tie(x, y) == tie(rhs.x, rhs.y);
	}
	pt operator/(i64 rhs) {
		assert(x % rhs == 0);
		assert(y % rhs == 0);
		return pt(x / rhs, y / rhs);
	}
};

// 1=ccw, 0=straight, -1=cw
int ccw(const pt& p0, const pt& p1, const pt& p2) {
	const auto r = (p1 - p0) ^ (p2 - p0);
	return r > 0 ? 1 : r < 0 ? -1 : 0;
}

struct frac {
	i64 n, d;
	frac(i64 n_, i64 d_) : n(n_), d(d_) {
		i64 g = gcd(n,d);
		n /= g, d /= g;
	}
};
ostream& operator<<(ostream& out, const frac& f) {
	out << f.n;
	if (f.d != 1) out << '/' << f.d;
	return out;
}

int main() {
	cin.tie(nullptr), ios::sync_with_stdio(false);

	u64 n;
	cin >> n;
	const auto clamp = [&](u64 i) { return i>=n ? i-=n : i; };
	vector<pt> poly(n);
	for (u64 i = 0; i < n; i++) {
		cin >> poly[i].x >> poly[i].y;
		poly[i].x *= 2, poly[i].y *= 2;
	}
	const auto c = (poly[0] + poly[n / 2]) / 2;
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

	vector<bool> concave(n);
	// 0b01 set iff (i+1) is in ccw direction, 0b10 set iff (i-1) is in ccw
	vector<uint8_t> type(n);
	for (u64 i = 0, j = 1, k = 2; i < j; i = j, j = k, k = clamp(k + 1)) {
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
		if (r >= 2*n and num_open == 2) {
			cout << frac(c.x, 2) << ' ' << frac(c.y, 2) << ' ' << frac((last + poly[i]).x, 4) << ' ' << frac((last + poly[i]).y, 4) << '\n';
			return 0;
		}
		array<vector<u64>, 4> pts;
		bool impossible = false;
		for ( ; ccw(c, poly[i], poly[order[ii]]) == 0; ii = clamp(ii + 1), r++) {
			pts[type[order[ii]]].emplace_back(order[ii]);
			if (__builtin_popcount(type[order[ii]]) % 2 == 0 and concave[order[ii]])
				impossible = true;
			last = poly[order[ii]];
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
					cout << frac(c.x, 2) << ' ' << frac(c.y, 2) << ' ' << frac(poly[i].x, 2) << ' ' << frac(poly[i].y, 2) << '\n';
					return 0;
				}
			}
		}
	}

	cout << "impossible\n";

	return 0;
}
