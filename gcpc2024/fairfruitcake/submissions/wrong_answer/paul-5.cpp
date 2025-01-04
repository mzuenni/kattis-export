#include <bits/stdc++.h>
using namespace std;
using i64 = long long;

struct point { i64 x, y; };

const point o{0, 0};

point operator+(point a, point b) { return {a.x+b.x, a.y+b.y}; }
point operator-(point a, point b) { return {a.x-b.x, a.y-b.y}; }

i64 operator*(point a, point b) { return a.x*b.x + a.y*b.y; } // dot product
i64 operator%(point a, point b) { return a.x*b.y - a.y*b.x; } // cross product

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
    vector<tuple<point,bool,int>> events;
    for (int i = 0; i < n; i++) {
        point p = a[i], q = a[(i+1)%n], r = a[(i+2)%n];
        if ((p%q > 0) != (q%r > 0)) {
            events.emplace_back(q, (p-q)%(r-q) < 0, q%r > 0 ? 1 : -1);
        }
        depth += (p.x < 0) != (q.x < 0) && (p.x < 0) == (p%q > 0);
    }
    depth = (depth+1) / 2;

    auto order = [&](bool ok, int add) {
        return (ok ? 1 : -2) * add;
    };

    sort(begin(events), end(events), [&](auto c, auto d) {
        auto [p, okp, addp] = c;
        auto [q, okq, addq] = d;
        if ((p < o) != (q < o)) return p < o;
        if (p%q != 0) return p%q > 0;
        return order(okp, addp) < order(okq, addq);
    });

    if (events.empty()) {
        printf("%lld/2 %lld/2 %lld/2 %lld/2\n", c.x, c.y, c.x+7, c.y);
        return 0;
    }

    point p = {0, 1};
    for (auto [q, _, add]: events) {
        if (depth == 1) {
            point r = p+q, u = c+r, v = c-r;
            printf("%lld/2 %lld/2 %lld/2 %lld/2\n", u.x, u.y, v.x, v.y);
            return 0;
        }
        depth += add, p = q;
    }
    cout << "impossible" << '\n';
}
