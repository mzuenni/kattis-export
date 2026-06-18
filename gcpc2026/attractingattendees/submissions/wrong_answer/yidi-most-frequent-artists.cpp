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
    vector<int> cnt2(n);
    for (int i=0; i<m; i++) {
        int k;
        cin >> k;
        a[i].resize(k);
        for (int& e : a[i]) cin >> e, e--, cnt2[e]++;
    }

    vector<int> ind(n);
    iota(all(ind), 0);
    sort(all(ind), [&](int i, int j) { return cnt2[i] > cnt2[j]; });
    double time = clock();
    vector<char> act(n);
    vector<int> cnt(n), ans;
    int ok = 0;
    for (int i : ind) {
        if (clock() - time > 3.8 * CLOCKS_PER_SEC) break;

        act[i] = true;
        ok++;
        ans.push_back(i);

        for (int j=0; j<m; j++) {
            int diff = 0;
            for (int e : a[j]) {
                if (act[e]) diff++;
                else diff--;
            }
            if (!a[j].empty() && diff >= 0) {
                for (int e : a[j]) {
                    cnt[e]++;
                    if (cnt[e] == c) ok--;
                }
                a[j].clear();
            }
        }
        if (ok == 0) {
            cout << "possible\n";
            cout << ssize(ans) << '\n';
            for (int e : ans) cout << e+1 << ' ';
            cout << '\n';
            exit(0);
        }
    }
    cout << "impossible\n";
}
