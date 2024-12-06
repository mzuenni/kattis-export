#include <iostream>
using namespace std;

const int N = 555;
int x[N], y[N], h[N];

int main() {
    int n; cin >> n;

    for (int i = 0; i < n; i++) {
        cin >> x[i] >> y[i] >> h[i];
    }

    for (int i = 0; i < n; i++) {
        int lo = 0, hi = h[i];
        while (hi-lo > 1) {
            int md = (lo+hi) / 2;
            bool ok = true;
            for (int j = 0; j < n; j++) {
                if (h[j] <= h[i]) continue;
                int dx = x[j]-x[i], dy = y[j]-y[i];
                if (md*md > dx*dx + dy*dy) ok = false;
            }
            (ok ? lo : hi) = md;
        }
        cout << lo << '\n';
    }
}
