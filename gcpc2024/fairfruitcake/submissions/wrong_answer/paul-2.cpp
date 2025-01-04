#include <bits/stdc++.h>
using namespace std;
using i64 = long long;

struct point { i64 x, y; };

const point o{0, 0};

point operator+(point a, point b) { return {a.x+b.x, a.y+b.y}; }
point operator-(point a, point b) { return {a.x-b.x, a.y-b.y}; }

i64 operator*(point a, point b) { return a.x*b.x + a.y*b.y; } // dot product
i64 operator%(point a, point b) { return a.x*b.y - a.y*b.x; } // cross product

point normalize(point p) {
    i64 g = abs(gcd(p.x, p.y));
    return {p.x/g, p.y/g};
}

bool operator<(point a, point b) { // lexicographical compare
	if (a.x != b.x) return a.x < b.x;
	return a.y < b.y;
}

int main() {
    int n; cin >> n;

    vector<point> a(n);
    for (auto &[x, y]: a) {
        cin >> x >> y;
        x *= 2, y *= 2;
    }
    
    point c = a[0] + a[n/2];
    c.x /= 2, c.y /= 2;

    for (auto &p: a) p = p-c;

    int depth = 0;
    vector<pair<point,int>> events;
    for (int i = 0; i < n; i++) {
        point p = normalize(a[i]), q = normalize(a[(i+1)%n]), r = normalize(a[(i+2)%n]);
        if ((p%q > 0) != (q%r > 0)) {
            events.emplace_back(q, q%r > 0 ? 1 : -1);
        }
        depth += (p.x < 0) != (q.x < 0) && (p.x < 0) == (p%q < 0);
    }
    depth = (depth+1) / 2;

    sort(begin(events), end(events), [&](auto c, auto d) {
        point p = c.first, q = d.first;
        if ((p < o) != (q < o)) return p < o;
        return p%q > 0;
    });

    if (events.empty()) {
        printf("%lld/2 %lld/2 %lld/2 %lld/2\n", c.x, c.y, c.x+7, c.y);
        return 0;
    }

    point p = events[0].first;
    for (auto [q, add]: events) {
        if (depth == 1 && p%q != 0) {
            point r = p+q, u = c+r, v = c-r;
            printf("%lld/2 %lld/2 %lld/2 %lld/2\n", u.x, u.y, v.x, v.y);
            return 0;
        }
        depth += add, p = q;
    }
    cout << "impossible" << '\n';
}
