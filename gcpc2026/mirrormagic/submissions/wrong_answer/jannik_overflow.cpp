
#include <cassert>
#include <cmath>
#include <iomanip>
#include <iostream>
#include <numeric>
#include <set>
#include <vector>

using namespace std;

#define int int64_t
#define sz(a) ((int)(a).size())
#define all(a) (a).begin(), (a).end()

using ld = long double;

struct frac {
	int n, d;
	auto operator<=>(const frac& r) const { return n * r.d <=> r.n * d; }
	frac& norm()
	{
		if (d < 0)
			d = -d, n = -n;
		int g = gcd(n, d);
		n /= g, d /= g;
		return *this;
	}
	frac(int n = 0, int d = 1)
		: n(n)
		, d(d)
	{
		norm();
	}
	frac operator-() const { return frac(-n, d); }
	frac& operator-=(const frac& r) { return *this = frac(n * r.d - r.n * d, r.d * d); }
	frac& operator+=(const frac& r) { return *this = frac(n * r.d + r.n * d, r.d * d); }
	frac& operator*=(const frac& r) { return *this = frac(n * r.n, d * r.d); }
	frac& operator/=(const frac& r) { return *this = frac(n * r.d, d * r.n); }
	frac& operator/=(int x) { return d *= x, norm(); }
#define OP(o, oe)                        \
	frac operator o(const frac& r) const \
	{                                    \
		frac l = *this;                  \
		return l oe r;                   \
	}
	OP(-, -=)
	OP(+, +=)
	OP(*, *=)
	OP(/, /=)
#undef OP
	frac operator/(int r) const
	{
		frac l = *this;
		return l /= r;
	}
	ld val() const { return n / (ld)d; }
};

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
using ptf = pt<frac>;

ptf avg(const auto& pts)
{
	pti sum { 0, 0 };
	for (const auto& p : pts)
		sum.x += p.x, sum.y += p.y;
	return ptf { frac(sum.x, sz(pts)), frac(sum.y, sz(pts)) };
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
	for (auto& [x, y] : a) {
		int a, b;
		cin >> a >> b;
		x = a, y = b;
	}
	for (int i = 0, x, y; i < n; i++)
		cin >> x >> y, b.emplace(x, y);
	ptf ca = avg(a), cb = avg(b);
	ptf c { (ca.x + cb.x) / 2, (ca.y + cb.y) / 2 };
	ptf normal = ca - c;

	for (auto [x, y] : a) {
		frac k = ((c - ptf(x, y)) * normal) / (normal * normal);
		if (k >= 0)
			fail();
		ptf pf = ptf(x, y) + normal * 2 * k;
		if (pf.x.d != 1 or pf.y.d != 1)
			fail();
		pti p(pf.x.n, pf.y.n);
		auto it = b.find(p);
		if (it == b.end())
			fail();
		b.erase(it);
	}

	cout << "possible\n";
}
