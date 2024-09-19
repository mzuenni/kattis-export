// @EXPECTED_RESULTS@: ACCEPTED, TIME_LIMIT_EXCEEDED
#include <algorithm>
#include <numeric>
#include <iostream>
#include <vector>

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
    for (int mask = 0; mask < (1 << w); mask++) {
        if (__builtin_popcount(mask) != c) {
            continue;
        }
        vector<int> cnts(h);
        for (int i = 0; i < h; i++) {
            for (int j = 0; j < w; j++) {
                if ((mask >> j) & 1 && g[i][j] == '.') {
                    cnts[i]++;
                }
            }
        }
        sort(cnts.rbegin(), cnts.rend());
        mx = max(mx, accumulate(cnts.begin(), cnts.begin() + r, 0));
    }
    cout << (double)mx / (r * c) << endl;
}
