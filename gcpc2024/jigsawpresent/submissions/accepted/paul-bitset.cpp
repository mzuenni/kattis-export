#include <bits/stdc++.h>
using namespace std;

template<typename F>
void sums(vector<pair<int,int>> a, F f) {
    int n = size(a);
    vector<pair<int,int>> s = {{0, 0}};
    for (int i = 0; i < n; i++) {
        auto [x, y] = a[i];
        for (int mask = 0; mask < (1 << i); mask++) {
            auto [sx, sy] = s[mask];
            s.emplace_back(sx+x, sy+y);
        }
    }

    for (int mask = 0; mask < (1 << n); mask++) {
        for (int smask = mask; ; smask = (smask-1) & mask) {
            auto [x1, y1] = s[smask];
            auto [x2, y2] = s[mask^smask];
            f(smask, mask^smask, x1-x2, y1-y2);
            if (smask == 0) break;
        }
    }
}

void print_mask(int mask) {
    cout << __builtin_popcount(mask);
    for (int i = 0; i < 32; i++) if (mask & (1 << i)) {
        cout << ' ' << i+1;
    }
    cout << '\n';
}

const int N = 114'884, M = N/2;
bitset<N> cacheL[N];

int main() {
    int n; cin >> n;
    vector<pair<int,int>> a(n);
    for (auto &[x, y]: a) cin >> x >> y;

    n = min(n, 28);
    int m = n/2;
    vector<pair<int,int>> aL(begin(a), begin(a)+m);
    vector<pair<int,int>> aR(begin(a)+m, begin(a)+n);

    sums(aL, [&](int mask1, int mask2, int x, int y) {
        (void) mask1, (void) mask2;
        cacheL[M+x][M+y] = 1;
    });

    bool found = false;
    int found_x, found_y, found_mask3, found_mask4;
    sums(aR, [&](int mask3, int mask4, int x, int y) {
        if (!found && (x != 0 || y != 0) && cacheL[M+x][M+y]) {
            found = true;
            found_x = x;
            found_y = y;
            found_mask3 = mask3;
            found_mask4 = mask4;
        }
    });

    if (!found) {
        cout << "yes" << '\n';
        return 0;
    }

    sums(aL, [&](int mask1, int mask2, int x, int y) {
        if (x == found_x && y == found_y) {
            cout << "no" << '\n';
            print_mask(mask2 | (found_mask3 << m));
            print_mask(mask1 | (found_mask4 << m));
            exit(0);
        }
    });
}
