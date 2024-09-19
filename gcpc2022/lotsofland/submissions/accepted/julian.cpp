#include <bits/stdc++.h>
using namespace std;

int main()
{
    ios::sync_with_stdio(false);

    int h, w, n;
    cin >> h >> w >> n;

    if (h * w % n) {
        cout << "impossible\n";
        return 0;
    }

    int hcnt = 1, wcnt = 1;
    for (int i = 2; i <= n; ++i) {
        while (n % i == 0) {
            n /= i;
            if (h % i == 0) {
                h /= i;
                hcnt *= i;
            } else {
                w /= i;
                wcnt *= i;
            }
        }
    }

    for (int i = 0; i < hcnt; ++i) {
        for (int ii = 0; ii < h; ++ii) {
            for (int j = 0; j < wcnt; ++j) {
                char c = 'A' + i * wcnt + j;
                for (int jj = 0; jj < w; ++jj) cout << c;
            }
            cout << "\n";
        }
    }
}
