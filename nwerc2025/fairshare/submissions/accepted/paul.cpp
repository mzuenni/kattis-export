#include <bits/stdc++.h>
using namespace std;

int main() {
    int n; cin >> n;
    vector<int> a(n), b(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i] >> b[i];
    }
    int sa = accumulate(begin(a), end(a), 0);
    int sb = accumulate(begin(b), end(b), 0);
    for (int i = 0; i < n; i++) {
        if (sb - sa <= b[i] - a[i]) {
            cout << i+1 << '\n';
            return 0;
        }
    }
    cout << "impossible" << '\n';
}
