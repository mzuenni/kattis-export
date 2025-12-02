#include <bits/stdc++.h>
using namespace std;

int lis(vector<int> a) {
    vector<int> dp, best = {INT_MIN};
    for (int x: a) {
        int cur = upper_bound(begin(best), end(best), x) - begin(best);
        dp.push_back(cur);
        if (cur == int(best.size())) best.push_back(x);
        best[cur] = min(best[cur], x);
    }
    return int(best.size()) - 1;
}

int main() {
    int n; cin >> n;
    vector<pair<int,int>> p;
    for (int i = 1; i <= n; i++) {
        int x; cin >> x;
        int len = n+1-x, j = i-len+1, k = i+len-1;
        // Can we go from (j,i) to (j,i-1)?
        if (j >= 1) p.emplace_back(2*j, -(2*i-1));
        // Can we go from (i,k) to (i+1,k)?
        if (k <= n) p.emplace_back(2*i+1, -2*k);
    }

    sort(begin(p), end(p));

    vector<int> a;
    for (auto [_, y]: p) a.push_back(y);
    cout << n - lis(a) << '\n';
}
