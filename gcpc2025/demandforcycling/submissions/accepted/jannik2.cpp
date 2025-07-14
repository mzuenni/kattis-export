#include <algorithm>
#include <cassert>
#include <iostream>
#include <list>
#include <map>
#include <set>
#include <vector>

using namespace std;

constexpr int oo = 0x3f3f3f3f;

using i64 = int64_t;
#define sz(a) ((i64)(a).size())
#define all(a) (a).begin(), (a).end()

struct pt {
	i64 x, y;
	pt() : x(0), y(0) { }
	pt(i64 x, i64 y) : x(x), y(y) { }
	pt(pair<i64, i64> p) : x(p.first), y(p.second) { }
	pt operator+(const pt& p) const { return pt(x + p.x, y + p.y); }
	pt operator-(const pt& p) const { return pt(x - p.x, y - p.y); }
	i64 operator*(const pt& p) const { return x * p.x + y * p.y; }
	pt operator*(const i64& t) const { return pt(x * t, y * t); }
	auto operator<(const pt& p) const { return (x == p.x) ? y < p.y : x < p.x; }
	auto operator>(const pt& p) const { return (x == p.x) ? y > p.y : x > p.x; }
	auto operator==(const pt& p) const { return x == p.x && y == p.y; }
};

int main()
{
	i64 n;
	cin >> n;
	vector<pt> poly(n);
	for (auto& [x, y] : poly)
		cin >> x >> y;

	map<i64, i64> hi, lo;
	for (auto [x, y] : poly) {
		auto [it, succ] = hi.emplace(x, y);
		if (not succ)
			it->second = max(it->second, y);
		tie(it, succ) = lo.emplace(x, y);
		if (not succ)
			it->second = min(it->second, y);
	}
	vector<pt> high(all(hi)), low(all(lo));
	const auto fix = [](vector<pt>& h, auto&& ma, i64 oo) {
		vector<i64> pref, suff;
		for (i64 i = 0, p = oo; i < sz(h); i++) {
			pref.emplace_back(p);
			p = ma(p, h[i].y);
		}
		for (i64 i = sz(h), p = oo; i-- > 0;) {
			suff.emplace_back(p);
			p = ma(p, h[i].y);
		}
		reverse(all(suff));
		vector<pt> res;
		for (i64 i = 0; i < sz(h); i++) {
			bool l = ma(pref[i], h[i].y) == h[i].y and pref[i] != h[i].y;
			bool r = ma(suff[i], h[i].y) == h[i].y and suff[i] != h[i].y;
			if (not l and not r)
				continue;
			assert(not l or not r);
			if (l) {
				if (not res.empty())
					res.emplace_back(h[i].x, res.back().y);
				res.emplace_back(h[i]);
			} else {
				if (not res.empty())
					res.emplace_back(res.back().x, h[i].y);
				res.emplace_back(h[i]);
			}
		}
		h = res;
	};
	fix(high, [](i64 a, i64 b) { return max(a, b); }, -oo);
	fix(low, [](i64 a, i64 b) { return min(a, b); }, oo);

	vector<pt> res = high;
	reverse(all(res));
	res.insert(res.end(), all(low));

	res.erase(unique(all(res)), res.end());

	cout << sz(res) << '\n';
	for (auto [x, y] : res)
		cout << x << ' ' << y << '\n';
}
