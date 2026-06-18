#include <bits/stdc++.h>
using namespace std;
using ll = int64_t;
#define all(x) ::begin(x), ::end(x)
#define debug(x...) [](auto&& ...y){ cerr << "["#x"]:"; ((cerr << ' ' << y), ...) << endl; }(x)

int main() {
    cin.tie(0)->sync_with_stdio(0);

    int n, m, c;
    cin >> n >> m >> c;
    vector<vector<int>> a(m);
    for (int i=0; i<m; i++) {
        int k;
        cin >> k;
        a[i].resize(k);
        for (int& e : a[i]) cin >> e, e--;
    }

    vector<int> ind(m);
    iota(all(ind), 0);
    mt19937 rng(42);
    shuffle(all(ind), rng);
    double time = clock();
    for (int i : ind) {
        if (clock() - time > 3.8 * CLOCKS_PER_SEC) break;

        vector<char> act(n);
        vector<int> cnt(n);
        for (int e : a[i]) act[e] = true;

        for (int j=0; j<m; j++) {
            int diff = 0;
            for (int e : a[j]) {
                if (act[e]) diff++;
                else diff--;
            }
            if (diff >= 0) {
                for (int e : a[j]) cnt[e]++;
            }
        }
        bool ok = true;
        for (int e : a[i]) if (cnt[e] < c) {
            ok = false;
            break;
        }
        if (ok) {
            cout << "possible\n";
            cout << ssize(a[i]) << '\n';
            for (int e : a[i]) cout << e+1 << ' ';
            cout << '\n';
            exit(0);
        }
    }
    cout << "impossible\n";
}
