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

const int X = 84'000;
bitset<2*X+1> cache[X+1];

template<typename F>
void dfs(int i, int mask, int sx, int sy, const F &f) {
    if (i == n) {
        f(mask, sx, sy);
    } else {
        dfs(i+1, mask, sx, sy, f);
        dfs(i+1, mask | (1 << i), sx+x[i], sy+y[i], f);
    }
}

int main() {
    cin >> n;
    n = min(n, N);
    for (int i = 0; i < n; i++) {
        cin >> x[i] >> y[i];
    }

    dfs(0, 0, 0, 0, [&](int mask1, int sx, int sy) {
        if (cache[sx][X+sy]) {
            cout << "no" << '\n';
            print_mask(mask1);
            dfs(0, 0, 0, 0, [&](int mask2, int tx, int ty) {
                if (tx == sx && ty == sy) {
                    print_mask(mask2);
                    exit(0);
                }
            });
        }
        cache[sx][X+sy] = 1;
    });
    cout << "yes" << '\n';
}
