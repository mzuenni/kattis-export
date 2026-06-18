#include <bits/stdc++.h>
using namespace std;

void fail() {
    cout << "impossible" << '\n';
    exit(0);
}

bool is_int(double x) {
    return abs(x-round(x)) / max(1.0, x) < 1e-6;
}

bool solve() {
    int n; cin >> n;
    vector<pair<int,int>> p(2*n);
    for (auto &[x, y]: p) cin >> x >> y;

    mt19937_64 gen(987);
    shuffle(begin(p), begin(p)+n, gen);
    shuffle(begin(p)+n, end(p), gen);

    vector<int> x(2*n), y(2*n);
    set<pair<int,int>> s(begin(p)+n, end(p));
    for (int i = 0; i < 2*n; i++) {
        tie(x[i], y[i]) = p[i];
    }

    for (int i = n; i < 2*n; i++) {
        double vx = y[i]-y[0], vy = x[0]-x[i];
        double vabs = hypot(vx, vy);
        if (vabs == 0) continue;
        vx /= vabs, vy /= vabs;

        double mx = 0.5 * (x[0]+x[i]), my = 0.5 * (y[0]+y[i]);

        bool ok = 1;
        for (int j = 0; j < n; j++) {
            double cross = (x[j]-mx) * vy - (y[j]-my) * vx;
            double qx = x[j] - 2 * cross * vy;
            double qy = y[j] + 2 * cross * vx;
            int rx = is_int(qx) ? round(qx) : x[j];
            int ry = is_int(qy) ? round(qy) : y[j];
            if (cross < 0 || !s.contains({rx, ry})) {
                ok = 0;
                break;
            }
        }
        if (ok) return 1;
    }
    return 0;
}

int main() {
    cout << (solve() ? "possible" : "impossible") << '\n';
}
