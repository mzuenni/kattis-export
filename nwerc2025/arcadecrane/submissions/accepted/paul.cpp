#include <bits/stdc++.h>
using namespace std;

const int k = 3;

int main() {
    int n; cin >> n;
    vector<int> a(n);
    for (int &x: a) cin >> x, x--;

    vector<pair<int,int>> steps;
    auto make_step = [&](int i, int j) {
        if (i == j || max(i, j) > n-k) return;
        steps.emplace_back(i, j);
        if (i < j) {
            rotate(begin(a)+i, begin(a)+i+k, begin(a)+j+k);
        } else {
            rotate(begin(a)+j, begin(a)+i, begin(a)+i+k);
        }
    };

    for (int i = n-1; i >= 2*k-1; i--) {
        if (a[i] == i) continue;
        int j = find(begin(a), end(a), i) - begin(a);
        if (j < k-1) {
            make_step(0, k-1);
            j = find(begin(a), end(a), i) - begin(a);
        }
        assert(j >= k-1);
        make_step(j-k+1, i-k+1);
    }

    srand(987);
    while (!is_sorted(begin(a), begin(a)+2*k-1)) {
        int i = rand() % k, j = rand() % k;
        if (i == j) continue;
        make_step(i, j);
    }

    cout << steps.size() << '\n';
    for (auto [i, j]: steps) {
        cout << i+1 << ' ' << j+1 << '\n';
    }
}
