#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
    int h = 7, w = 24;
    vector<string> g(h);
    for (int i = 0; i < h; i++) {
        cin >> g[i];
    }
    int r, c;
    cin >> r >> c;
    int mx = 0;
    for (int i = 0; i < (1 << h); i++) {
        if (__builtin_popcount(i) != r) {
            continue;
        }
        for (int j = 0; j < (1 << w); j++) {
            if (__builtin_popcount(j) != c) {
                continue;
            }
            int count = 0;
            for (int k = 0; k < h; k++) {
                if (i & (1 << k)) {
                    for (int l = 0; l < w; l++) {
                        if (j & (1 << l) && g[k][l] == '.') {
                            count++;
                        }
                    }
                }
            }
            mx = max(mx, count);
        }
    }
    cout << (double)mx / (r * c) << endl;
}
