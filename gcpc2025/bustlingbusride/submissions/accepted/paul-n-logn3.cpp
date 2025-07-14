#include <bits/stdc++.h>
using namespace std;
using i64 = long long;

int main() {
    int n, m, gap, onoff;
    cin >> n >> m >> gap >> onoff;
    vector<int> p(m), xs(n);
    for (int &x: p) cin >> x;
    for (int i = 1; i < m; i++) p[i] += p[i-1];
    for (int &x: xs) cin >> x, x = p[x-1];

    auto cost = [&](int from, int to) {
        vector<int> ys(begin(xs)+from, begin(xs)+to);
        sort(begin(ys), end(ys));
        i64 res = ys.back(), k = 0, x = 0;
        for (i64 y: ys) {
            k += y > x;
            res += 2*k*onoff;
            x = y;
        }
        return res;
    };

    auto solve = [&](i64 T) {
        for (int i = 0, k = 0; i < n; k++) {
            auto ok = [&](int j) { return i64(k)*gap + cost(i, j) <= T; };
            int step = 1;
            while (i+step <= n && ok(i+step)) step *= 2;
            int lo = i, hi = min(n+1, i+step);
            while (hi-lo > 1) {
                int md = (lo+hi) / 2;
                (ok(md) ? lo : hi) = md;
            }
            if (lo == i) return false;
            i = lo;
        }
        return true;
    };

    i64 lo = 0, hi = 1e13;
    while (hi-lo > 1) {
        i64 md = (lo+hi) / 2;
        (solve(md) ? hi : lo) = md;
    }
    cout << hi << '\n';
}
