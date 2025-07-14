#include <iostream>

using namespace std;

int main() {
    cin.tie(0);
    ios_base::sync_with_stdio(0);

    int n;
    cin >> n;
    int xl = 1e9 + 1, xr = -1;
    int yl = 1e9 + 1, yr = -1;
    for (int i = 0; i < n; i++) {
        int x, y;
        cin >> x >> y;
        xl = min(x, xl);
        xr = max(x, xr);
        yl = min(y, yl);
        yr = max(y, yr);
    }
    cout << 4 << endl;
    cout << xl << ' ' << yl << endl;
    cout << xr << ' ' << yl << endl;
    cout << xr << ' ' << yr << endl;
    cout << xl << ' ' << yr << endl;

    return 0;
}