#include <bits/stdc++.h>
using namespace std;

int main() {
    int m, n, u, v;
    cin >> m >> n >> u >> v;

    vector<int> a(m), b(n);
    for (int &x: a) cin >> x;
    for (int &x: b) cin >> x;
    sort(begin(a), end(a));
    sort(begin(b), end(b));


    auto check = [&](int k) {
        int i = 0;
        vector<int> use(m);
        for (int x: b) {
            while (i < m && (x > a[i] || use[i] >= (i < k ? v : u))) i++;
            if (i == m) return false;
            use[i]++;
        }
        return true;       
    };

    int lo = -1, hi = m+1;
    while (hi-lo > 1) {
        int md = (lo+hi) / 2;
        (check(md) ? lo : hi) = md;
    }

    if (lo >= 0) cout << lo << '\n';
    else cout << "impossible" << '\n';
}
