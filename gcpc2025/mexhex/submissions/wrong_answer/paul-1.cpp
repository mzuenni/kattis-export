#include <bits/stdc++.h>
using namespace std;

bool solve(int len, vector<int> v) {
    if (v.empty()) return true;
    int earliest_start = max(v[0]-len+1, 0);
    int latest_start = v[0];
    int prev = v[0];
    for (int cur: v) {
        if (cur-prev < len) {
            earliest_start = max(cur-len+1, 0);
        } else {
            earliest_start = max(earliest_start + 2*len, cur-len+1);
            latest_start = cur;
        }
        if (earliest_start > latest_start) return false;
        prev = cur;
    }
    return true;
}

bool solve_naive(int len, vector<int> v) {

}

int main() {
    int n, d;
    cin >> n >> d;
    vector<int> p(n);
    for (int &x: p) cin >> x;

    vector<vector<int>> occs(n+1);
    for (int i = 0; i < n; i++) {
        occs[p[i]].push_back(i);
    }

    for (int i = 0; i <= n; i++) {
        if (solve(d, occs[i])) {
            cout << i << '\n';
            break;
        }
    }
}
