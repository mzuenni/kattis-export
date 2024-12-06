#include <bits/stdc++.h>
using namespace std;

int ask(int i, int j) {
    cout << "? " << i << " " << j << endl;
    int r;
    cin >> r;
    if (j == r) {
        cout << "! " << i << " " << j << endl;
        exit(0);
    }
    return r;
}

int main() {
    int n;
    cin >> n;
    int x = ask(n, 1);
    const int t = (int) sqrt(n);
    map<int, int> loc;
    loc[x] = 0;
    for (int i = 1; i <= t; i++) {
        int r = ask(i, x);
        loc[r] = i;
    }
    for (int i = 2; i * t <= n; i++) {
        int r = ask(i * t, x);
        if (loc.count(r)) {
            ask(i * t - loc[r], x);
            assert(false);
        }
    }
    for (int i = n / t * t; i <= n; i++) {
        ask(i, x);
    }
    assert(false);
    return 0;
}
