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
        p_cnt[i] = p_cnt[i] / 2 + 1;
    }

    vector<int> rem;
    for (int i=0; i<n; i++) if (b_cnt[i] < c) rem.push_back(i);
    for (int i=0; i<ssize(rem); i++) {
        int x = rem[i];
        for (int p : a[x]) if (--p_cnt[p] == 0) {
            for (int b : a2[p]) if (b_cnt[b]-- == c) rem.push_back(b);
        }
    }

    vector<int> ans;
    sort(all(rem));
    rem.push_back(n);
    for (int i=0, j=0; i<n; i++) {
        if (i == rem[j]) j++;
        else ans.push_back(i);
    }

    if (ans.empty()) cout << "impossible\n";
    else {
        cout << "possible\n";
        cout << ssize(ans) << '\n';
        for (int e : ans) cout << e+1 << ' ';
        cout << '\n';
    }
}
