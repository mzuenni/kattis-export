#include <bits/stdc++.h>
using namespace std;

int main() {
    int n;
    cin >> n;
    vector<int> x(n), y(n), h(n);
    for (int i = 0; i < n; i++) {
        cin >> x[i] >> y[i] >> h[i];
    }

    for (int i = 0; i < n; i++) {
        int r = h[i];
        for (int j = 0; j < n; j++) {
            if (h[j] > h[i]) {
                int d = ((x[i] - x[j]) * (x[i] - x[j])) + ((y[i] - y[j]) * (y[i] - y[j]));
                r = min(r, int(floor(sqrt(d))));
            }
        }
        cout << r << '\n';
    }
    return 0;
}
