#include <bits/stdc++.h>
using namespace std;
using ll = int64_t;
#define all(x) ::begin(x), ::end(x)
void _d(auto... x) { ((cerr << ' ' << x), ...) << endl; }
#define debug(x...) cerr << "["#x"]:", _d(x)

int main() {
    cin.tie(0)->sync_with_stdio(0);

    int n;
    cin >> n;
    int MX = 1e6 + 5;
    vector<vector<array<int, 2>>> a(MX);
    for (int i=0; i<2*n; i++) {
        int l, r, c;
        cin >> l >> r >> c;
        a[c].push_back({l, r});
    }

    vector<int> groups[2] = {};
    ll ans = 0;

    auto add = [&](int g, int c, array<int, 2> x) {
        ans += x[g];
        groups[g].push_back(x[!g] - x[g] - c);
    };

    for (int c=0; c<MX; c++) {
        sort(all(a[c]), [](auto& x, auto& y) { return x[0] - x[1] > y[0] - y[1]; });
        if (ssize(a[c]) % 2 == 1) {
            int mid = ssize(a[c]) / 2;
            add(ssize(groups[0]) > ssize(groups[1]), 0, a[c][mid]);
        }

        for (int i=0; i<ssize(a[c])/2; i++) {
            add(0, c, a[c][i]);
            add(1, c, a[c].end()[-1 - i]);
            ans += c;
        }
    }

    sort(all(groups[0]));
    sort(all(groups[1]));
    for (int i=n-1; i>=0 && groups[0][i] + groups[1][i] > 0; i--) {
        ans += groups[0][i] + groups[1][i];
    }

    cout << ans << '\n';
}
