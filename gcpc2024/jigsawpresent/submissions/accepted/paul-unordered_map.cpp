#include <bits/stdc++.h>
using namespace std;
using i64 = long long;

const int N = 265432;

template<typename F>
void sums(vector<int> a, F f) {
    int n = size(a);
    vector<i64> s = {0};
    for (int i = 0; i < n; i++) {
        for (int mask = 0; mask < (1 << i); mask++) {
            s.push_back(s[mask] + a[i]);
        }
    }

    for (int mask = 0; mask < (1 << n); mask++) {
        for (int smask = mask; ; smask = (smask-1) & mask) {
            f(smask, mask^smask, s[smask] - s[mask^smask]);
            if (smask == 0) break;
        }
    }
}

void print_mask(int mask) {
    cout << __builtin_popcount(mask);
    for (int i = 0; i < 28; i++) if (mask & (1 << i)) {
        cout << ' ' << i+1;
    }
    cout << '\n';
}

int main() {
    int n; cin >> n;
    vector<int> a(n);
    for (int i = 0; i < n; i++) {
        int x, y;
        cin >> x >> y;
        a[i] = x*N + y;
    }

    n = min(n, 28);
    int m = n/2;
    vector<int> aL(begin(a), begin(a)+m);
    vector<int> aR(begin(a)+m, begin(a)+n);

    unordered_map<i64, pair<int,int>> cacheL;
    sums(aL, [&](int mask1, int mask2, i64 cur) {
        cacheL[cur] = {mask1, mask2};
    });

    bool found = false;
    sums(aR, [&](int mask3, int mask4, i64 cur) {
        if (!found && cur != 0 && cacheL.count(cur)) {
            found = true;
            auto [mask1, mask2] = cacheL[cur];
            cout << "no" << '\n';
            print_mask(mask2 | (mask3 << m));
            print_mask(mask1 | (mask4 << m));
        }
    });

    if (!found) cout << "yes" << '\n';
}
