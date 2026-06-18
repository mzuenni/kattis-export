#include <cassert>
#include <cmath>
#include <iomanip>
#include <iostream>
#include <set>
#include <vector>

using namespace std;

#define int int64_t
#define sz(a) ((int)(a).size())
#define all(a) (a).begin(), (a).end()

template <typename T>
struct pt {
	T x, y;
	auto operator<=>(const pt&) const = default;
	pt& operator-=(const pt& r) { return x -= r.x, y -= r.y, *this; }
	pt& operator+=(const pt& r) { return x += r.x, y += r.y, *this; }
	pt& operator*=(const T& r) { return x *= r, y *= r, *this; }
	pt& operator/=(const T& r) { return x /= r, y /= r, *this; }
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
	T operator*(const pt& r) const { return x * r.x + y * r.y; }
	pt operator*(const T& r) const
	{
		pt l = *this;
		return l *= r;
	}
};
using pti = pt<int>;
using ptf = pt<long double>;

ptf avg(const auto& pts)
{
	ptf sum { 0, 0 };
	for (const auto& p : pts)
		sum.x += p.x, sum.y += p.y;
	return ptf { sum.x / (float)sz(pts), sum.y / (float)sz(pts) };
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
	vector<pti> a(n);
	set<pti> b;
	for (auto& [x, y] : a)
		cin >> x >> y;
	for (int i = 0, x, y; i < n; i++)
		cin >> x >> y, b.emplace(x, y);
	ptf ca = avg(a), cb = avg(b);
	ptf c { (ca.x + cb.x) / 2, (ca.y + cb.y) / 2 };
	ptf normal = ca - c;

	// for (auto [x, y] : b) {
	// 	float k = ((c - ptf(x, y)) * normal) / (normal * normal);
	// 	if (k <= 0)
	// 		fail();
	// }
	for (auto [x, y] : a) {
		float k = ((c - ptf(x, y)) * normal) / (normal * normal);
		if (k >= 0)
			fail();
		ptf pf = ptf(x, y) + normal * 2 * k;
		pti p(round(pf.x), round(pf.y));
		auto it = b.find(p);
		if (it == b.end())
			fail();
		b.erase(it);
	}

	cout << "possible\n";
}
