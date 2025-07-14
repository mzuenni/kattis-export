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

    vector<bool> ffs(n);
    auto solve = [&](i64 T) {
        for (int i = 0, k = 0; i < n; k++) {
            i64 count = 0;
            int j = i, xmax = 0;
            for (; j < n; j++) {
                ffs[j] = true;
                xmax = max(xmax, xs[j]);
                i64 jwf = 0, wfj = 0;
                for (int k = i; k < j; k++) {
                    if (xs[k] == xs[j]) ffs[j] = false;
                    if (xs[k] > xs[j]) wfj++;
                    if (xs[k] < xs[j] && ffs[k]) jwf++;
                }
                if (!ffs[j]) wfj = 0;
                count += jwf + wfj + 1;
                if (i64(k)*gap + 2*count*onoff + xmax > T) {
                    if (j == i) return false;
                    break;
                }
            }
            i = j;
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
