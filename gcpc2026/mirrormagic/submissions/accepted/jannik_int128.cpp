#include <cassert>
#include <cmath>
#include <iomanip>
#include <iostream>
#include <set>
#include <vector>

using namespace std;

#define int int64_t
using i128 = __int128_t;
using ld = long double;
#define sz(a) ((int)(a).size())

struct pt {
	i128 x, y;
	auto operator<=>(const pt&) const = default;
	pt& operator-=(const pt& r) { return x -= r.x, y -= r.y, *this; }
	pt& operator+=(const pt& r) { return x += r.x, y += r.y, *this; }
	pt& operator*=(const i128& r) { return x *= r, y *= r, *this; }
	pt operator-(const pt& r) const
	{
		pt l = *this;
		return l -= r;
	}
	pt operator+(const pt& r) const
	{
		pt l = *this;
		return l += r;
	}
	i128 operator*(const pt& r) const { return x * r.x + y * r.y; }
	pt operator*(const i128& r) const
	{
		pt l = *this;
		return l *= r;
	}
};

pt avg(const auto& pts)
{
	pt sum { 0, 0 };
	for (const auto& p : pts)
		sum.x += p.x, sum.y += p.y;
	assert(sum.x % sz(pts) == 0);
	assert(sum.y % sz(pts) == 0);
	return pt { sum.x / sz(pts), sum.y / sz(pts) };
}

void fail()
{
	cout << "impossible\n";
	exit(0);
}

signed main()
{
	int n;
	cin >> n;
	vector<pt> a(n);
	set<pt> b;
	for (auto& [x, y] : a) {
		int a, b;
		cin >> a >> b;
		x = a * n * 2, y = b * n * 2;
	}
	for (int i = 0, x, y; i < n; i++) {
		cin >> x >> y;
		b.emplace(x * n * 2, y * n * 2);
	}
	pt ca = avg(a), cb = avg(b);
	assert((ca.x + cb.x) % 2 == 0);
	assert((ca.y + cb.y) % 2 == 0);
	pt c { (ca.x + cb.x) / 2, (ca.y + cb.y) / 2 };
	pt normal = ca - c;
	const i128 normal_len2 = normal * normal;
	// 2*n*maxcoord <= 2*10^11

	for (pt p : b) { // this should be unnecessary because of symmetry
		i128 k = (c - p) * normal * 2;
		if (k <= 0)
			fail();
	}
	for (pt p : a) {
		i128 k = (c - p) * normal * 2;
		if (k >= 0)
			fail();
		pt tmp = normal * k;
		if (tmp.x % normal_len2 or tmp.y % normal_len2)
			fail();
		tmp.x /= normal_len2, tmp.y /= normal_len2;
		pt pf = p + tmp;
		auto it = b.find(pf);
		if (it == b.end())
			fail();
		b.erase(it);
	}

	cout << "possible\n";
}
