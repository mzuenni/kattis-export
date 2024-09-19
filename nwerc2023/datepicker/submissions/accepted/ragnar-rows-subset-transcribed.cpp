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
    for (int mask = 0; mask < (1 << h); mask++) {
        if (__builtin_popcount(mask) != r) {
            continue;
        }
        vector<int> cnts(w);
        for (int j = 0; j < w; j++) {
            for (int i = 0; i < h; i++) {
                if ((mask >> i) & 1 && g[i][j] == '.') {
                    cnts[j]++;
                }
            }
        }
        sort(cnts.rbegin(), cnts.rend());
        mx = max(mx, accumulate(cnts.begin(), cnts.begin() + c, 0));
    }
    cout << (double)mx / (r * c) << endl;
}
