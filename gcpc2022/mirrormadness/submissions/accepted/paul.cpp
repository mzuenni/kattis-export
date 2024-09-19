#include <cassert>
#include <iostream>
#include <set>
#include <vector>
using namespace std;

int signum(int x) { return (x > 0) - (x < 0); }

struct point {
	int x, y;
	bool operator<(const point &p) const { return x+y < p.x+p.y; }
};

int dist(point a, point b) { return abs(a.x-b.x) + abs(a.y-b.y); }

struct match {
	int i, j, ifrom, jfrom, len;
	bool operator<(const match &m) const { return ifrom < m.ifrom; }
};

void northwest_matching(const vector<point> &a, vector<vector<match>> &v) {
	int n = size(a);
	vector<pair<int,int>> events;
	for (int i = 0; i < n; i++) {
		point p = a[i], q = a[(i+1)%n];
		if (q < p) swap(p,q);
		events.emplace_back(p.x+p.y, i);
		events.emplace_back(q.x+q.y, ~i);
	}
	sort(begin(events), end(events));

	set<int> active;
	auto make_matches = [&](int z1, int z2) {
		int z = (z1+z2)/2;
		assert(size(active)%2 == 0);
		
		vector<pair<int,int>> events2;
		for (int i: active) {
			point p = a[i], q = a[(i+1)%n];
			events2.emplace_back(p.x == q.x ? p.x : z-p.y, i);
		}
		sort(begin(events2), end(events2));
		
		for (int k = 0; k < ssize(events2); k += 2) {
			int i = events2[k].second, j = events2[k+1].second;
			int zi = a[i].x + a[i].y, zj = a[j].x + a[j].y;
			int ifrom = min(abs(z1-zi), abs(z2-zi));
			int jfrom = min(abs(z1-zj), abs(z2-zj));
			v[i].push_back({i, j, ifrom, jfrom, z2-z1});
		}
	};

	int pz = -1e9;
	for (auto [z,i]: events) {
		if (pz < z) {
			make_matches(pz, z);
		}
		if (i >= 0) active.insert(i);
		else active.erase(~i);
		pz = z;	
	}
}

int main() {
	int n, m;
	cin >> n >> m;

	vector<point> a(n);
	for (auto &[x,y]: a) cin >> x >> y;

	// 0: NW, 1: NE, 2: SE, 3: SW
	vector<vector<vector<match>>> matchings(2, vector<vector<match>>(n));
	for (int dir = 0; dir < 4; dir++) {
		northwest_matching(a, matchings[dir%2]);
		for (auto &[x,y]: a) y = -y, swap(x,y); // rotate CCW
	}

	for (auto &u: matchings) for (auto &v: u) sort(begin(v), end(v));

	auto on_segment = [&](int i, point s) {
		point p = a[i], q = a[(i+1)%n];
		if (q < p) swap(p,q);
		return p.x <= s.x && s.x <= q.x && p.y <= s.y && s.y <= q.y;
	};

	point s;
	cin >> s.x >> s.y;
	int i = 0, dir = 1;
	while (!on_segment(i,s)) i++;
	int ipos = dist(a[i],s);

	while (m--) {
		auto &v = matchings[dir][i];
		auto m = *prev(lower_bound(begin(v), end(v), match{0,0,ipos,0,0}));
		i = m.j, ipos = m.jfrom + m.ifrom + m.len - ipos, dir = 1-dir;
		point p = a[i], q = a[(i+1)%n];
		cout << (p.x + signum(q.x-p.x)*ipos) << ' ' << (p.y + signum(q.y-p.y)*ipos) << '\n';
	}
}
