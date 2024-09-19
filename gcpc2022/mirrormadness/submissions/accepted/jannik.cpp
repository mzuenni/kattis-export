#include <vector>
#include <algorithm>
#include <iostream>
#include <map>
#include <cassert>

using namespace std;

using ll = long long;

#define all(a) (a).begin(),(a).end()
#define sz(a) ll((a).size())
#define MP make_pair

constexpr ll oo = 0x3f3f3f3f3f3f3f3fLL;

struct pt {
	ll x,y;
	pt(ll x, ll y) : x(x), y(y) {}
	pt() : pt(0,0) {}
	pt operator+(const pt& a) const { return pt(x + a.x, y + a.y); }
	pt operator-(const pt& a) const { return pt(x - a.x, y - a.y); }
	pt& operator+=(const pt& a) { *this = *this + a; return *this; }
	bool operator==(const pt& a) const { return tie(x,y) == tie(a.x,a.y); }
	bool operator!=(const pt& a) const { return !(*this == a); }
	bool operator<(const pt& a) const { return tie(x,y) < tie(a.x,a.y); }
};
pt operator-(const pt& a) { return pt(-a.x, -a.y); }

ll sign(ll x) { return (x > 0) - (x < 0); }
pt normalise(const pt& a) { return pt(sign(a.x), sign(a.y)); }
pt flipX(const pt& a) { return pt(-a.x, a.y); }
pt flipY(const pt& a) { return pt(a.x, -a.y); }

ll diag(const pt& p, bool lr) { // lr = false: /, true: \.
	if (lr)
		return p.y - p.x;
	else
		return p.x + p.y;
}

int main() {
	ll n, m;
	cin >> n >> m;

	vector<pt> poly(n);
	for (pt& p : poly) cin >> p.x >> p.y;

	map<ll, vector<pair<pt, bool>>> diagonals[2]; // {0 : /, 1: \} -> (pt, horizontal)

	for (ll i = 0; i < n; i++) {
		const pt p1 = poly[i], p2 = poly[(i+1)%n];

		const pt dir = normalise(p2 - p1);
		assert(dir.x != 0 || dir.y != 0);

		for (pt p = dir + p1; p != p2; p += dir)
			for (ll d = 0; d < 2; d++)
				diagonals[d][diag(p, d)].emplace_back(p, !!dir.x);
	}
	vector<pair<pt, pair<pt,ll>>> adj[4];
	const auto ix = [](pt a) {
		a = normalise(a);
		assert(abs(a.x) + abs(a.y) == 2);
		return (a.x + 1) + (a.y + 1) / 2;
	};
	for (ll d = 0; d < 2; d++)
		for (auto&[di,vs] : diagonals[d]) {
			sort(all(vs), [&](const auto& p1, const auto& p2) {
				return diag(p1.first, !d) < diag(p2.first, !d);
			});
			for (ll i = 0; i < sz(vs) - 1; i++) {
				const auto p0 = vs[i].first, p1 = vs[i+1].first;
				const auto dir = p1 - p0;
				adj[ix( dir)].emplace_back(p0, MP(p1, ix(vs[i+1].second ? flipY( dir) : flipX( dir))));
				adj[ix(-dir)].emplace_back(p1, MP(p0, ix(vs[i  ].second ? flipY(-dir) : flipX(-dir))));
			}
		}

	for (ll i = 0; i < 4; i++)
		sort(all(adj[i]));

	pt s;
	cin >> s.x >> s.y;
	ll dir = 3;

	while (m-- > 0) {
		tie(s, dir) = lower_bound(all(adj[dir]), MP(s, MP(pt(-oo,-oo), -oo)))->second;
		cout << s.x << ' ' << s.y << endl;
	}

	return 0;
}
