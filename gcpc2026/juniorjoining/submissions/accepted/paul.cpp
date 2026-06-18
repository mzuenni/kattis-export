#include <bits/stdc++.h>
using namespace std;

int main() {
    int n; cin >> n;

    long base = 0;
    map<int,vector<int>> diffs;
    for (int i = 0; i < 2*n; i++) {
        int l, r, c;
        cin >> l >> r >> c;
        base += r;
        diffs[c].push_back(l-r);
    }

    vector<int> w;
    for (auto [c, v]: diffs) {
        int k = v.size();
        sort(begin(v), end(v), greater());
        for (int i = 0; i < k/2; i++) {
            v[i] += c;
            v[k-1-i] -= c;
        }
        copy(begin(v), end(v), back_inserter(w));
    }

    sort(begin(w), end(w), greater());
    cout << base + accumulate(begin(w), begin(w)+n, 0L) << '\n';
}
