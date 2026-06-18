#include <bits/stdc++.h>
using namespace std;
using ll = int64_t;
#define all(x) ::begin(x), ::end(x)
#define debug(x...) [](auto&& ...y){ cerr << "["#x"]:"; ((cerr << ' ' << y), ...) << endl; }(x)

int main() {
    cin.tie(0)->sync_with_stdio(0);

    int n, m, c;
    cin >> n >> m >> c;
    vector<vector<int>> a(n), a2(m);
    vector<int> b_cnt(n), p_cnt(m);
    for (int i=0; i<m; i++) {
        cin >> p_cnt[i];
        a2[i].resize(p_cnt[i]);
        for (int& e : a2[i]) {
            cin >> e;
            a[--e].push_back(i);
            b_cnt[e]++;
        }
        p_cnt[i] = (p_cnt[i]+1) / 2;
    }

    vector<bool> used_b(n, true), used_p(m, true);;
    vector<int> check(n);
    iota(all(check), 0);
    while (!check.empty()) {
        int x = check.back();
        check.pop_back();
        if (!used_b[x] || b_cnt[x] >= c) continue;
        used_b[x] = false;
        for (int p : a[x]) if (used_p[p]) {
            if (--p_cnt[p] == 0) {
                for (int b : a2[p]) {
                    b_cnt[b]--;
                    check.push_back(b);
                }
            }
        }
    }

    vector<int> ans;
    for (int i=0; i<n; i++) if (used_b[i]) ans.push_back(i);

    if (ans.empty()) cout << "impossible\n";
    else {
        cout << "possible\n";
        cout << ssize(ans) << '\n';
        for (int e : ans) cout << e+1 << ' ';
        cout << '\n';
    }
}
