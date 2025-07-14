#include <bits/stdc++.h>
using namespace std;

int main() {
    int h, w;
    cin >> h >> w;

    vector<string> a(h);
    for (string &s: a) cin >> s;

    int total = 0;
    for (string s: a) for (char c: s) total += c == '#';

    auto solve = [&](int n) {
        vector mark(h, vector<int>(w));
        for (int i = 0; i < h; i++) {
            for (int j = 0; j < w; j++) {
                if (a[i][j] == '#' && !mark[i][j]) {
                    if (i+n > h || j+n > w) return false;
                    for (int di = 0; di < n; di++) {
                        for (int dj = 0; dj < n; dj++) {
                            if (a[i+di][j+dj] == '.') return false;
                            mark[i+di][j+dj] = 1;
                        }
                    }
                }
            }
        }
        return true;
    };

    for (int n = min(h, w); ; n--) {
        if (total % (n*n) == 0 && solve(n)) {
            cout << n << '\n';
            break;
        }
    }
}
