#include <bits/stdc++.h>
using namespace std;

void print_mask(int mask) {
    cout << __builtin_popcount(mask);
    for (int i = 0; i < 32; i++) if (mask & (1 << i)) {
        cout << ' ' << i+1;
    }
    cout << '\n';
}

const int N = 28, K = N/2;
int n, x[N], y[N];
int sxL[1 << K], syL[1 << K], sxR[1 << K], syR[1 << K];

pair<int,int> sum(int mask) {
    int tx = sxL[mask % (1 << K)] + sxR[mask >> K];
    int ty = syL[mask % (1 << K)] + syR[mask >> K];
    return make_pair(tx, ty);
}

const int X = 84'000;
bitset<2*X+1> cache[X+1];

int main() {
    cin >> n;
    n = min(n, N);
    for (int i = 0; i < n; i++) {
        cin >> x[i] >> y[i];
    }

    for (int i = 0; i < min(n, K); i++) {
        for (int mask = 0; mask < (1 << i); mask++) {
            sxL[mask | (1 << i)] = sxL[mask] + x[i];
            syL[mask | (1 << i)] = syL[mask] + y[i];
        }
    }
    for (int i = K; i < min(n, N); i++) {
        for (int mask = 0; mask < (1 << (i-K)); mask++) {
            sxR[mask | (1 << (i-K))] = sxR[mask] + x[i];
            syR[mask | (1 << (i-K))] = syR[mask] + y[i];
        }
    }

    for (int mask1 = 1; mask1 < (1 << n); mask1++) {
        auto [sx, sy] = sum(mask1);
        if (!(sx <= X && 0 <= X+sy && X+sy <= 2*X)) continue;
        if (cache[sx][X+sy]) {
            cout << "no" << '\n';
            print_mask(mask1);
            for (int mask2 = 1; ; mask2++) {
                auto [tx, ty] = sum(mask2);
                if (tx == sx && ty == sy) {
                    print_mask(mask2);
                    return 0;
                }
            }
        }
        cache[sx][X+sy] = 1;
    }
    cout << "yes" << '\n';
}
