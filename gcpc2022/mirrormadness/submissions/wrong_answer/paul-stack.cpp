#include <bits/stdc++.h>
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
	int s = min_element(begin(a), end(a)) - begin(a);

	stack<pair<int,int>> stk;
	for (int k = 0; k < n; k++) {
		int j = (s+k)%n;
		point p = a[j], q = a[(j+1)%n];
		int jpos = 0, jlen = dist(p,q);
		if (p < q) {
			stk.push({j,jlen});
		} else {
			while (true) {
				auto &[i,ilen] = stk.top();
				int len = min(ilen, jlen-jpos);
				v[j].push_back({j,i,jpos,ilen-len,len});
				ilen -= len, jpos += len;
				if (ilen == 0) stk.pop();
				if (jpos == jlen) break;
			}
		}
	}
	assert(stk.empty());
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
