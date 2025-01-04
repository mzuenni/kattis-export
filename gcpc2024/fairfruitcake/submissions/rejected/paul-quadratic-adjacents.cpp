// @EXPECTED_RESULTS@: WRONG_ANSWER, TIME_LIMIT_EXCEEDED
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

point normalize(point a) {
    i64 g = abs(gcd(a.x, a.y));
    a.x /= g, a.y /= g;
    if (a < o) a = o-a;
    return a;
}

bool operator==(point a, point b) {
    return a.x == b.x && a.y == b.y;
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
    a.push_back(a[0]);
    a.push_back(a[1]);
    a.push_back(a[2]);

    vector<point> directions;
    for (int i = 0; i < n; i++) {
        directions.push_back(normalize(a[i]));
        directions.push_back(normalize(a[i] + a[i+1]));
    }
    sort(begin(directions), end(directions));
    auto it = unique(begin(directions), end(directions));
    directions.erase(it, end(directions));

    for (point dir: directions) {
        auto opp = [&](i64 y1, i64 y2) { return (y1 < 0) != (y2 < 0); };

        int count = 0;
        for (int i = 0; i < n; i++) {
            point p = a[i], q = a[i+1], r = a[i+2], s = a[i+3];
            i64 py = dir%p, qy = dir%q, ry = dir%r, sy = dir%s;
            if (py == 0) continue;
            if (qy != 0) {
                count += opp(py, qy);
            } else if (ry != 0) {
                if (opp(py, ry)) count += true;
                else count += (q-p) % (r-p) < 0;
            } else {
                if (opp(py, sy)) count += true;
                else count += (py < 0) == (q*dir < r*dir);
            }
            if (count > 2) break;
        }
        if (count == 2) {
            point u = c+dir, v = c-dir;
            printf("%lld/2 %lld/2 %lld/2 %lld/2\n", u.x, u.y, v.x, v.y);
            return 0;
        }
    }
    cout << "impossible" << '\n';
}
