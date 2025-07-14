#include <bits/stdc++.h>
using namespace std;

int main() {
    int n, a, b;
    cin >> n >> a >> b;

    vector<int> h(n);
    iota(begin(h), end(h), 1);

    do {
        vector<int> vl(n, 1), vr(n, 1);
        for (int i = 0; i < n; i++) {
            for (int j = i+1; j < n; j++) {
                if (h[i] < h[j]) vr[i] = 0;
                else vl[j] = 0;
            }
        }
        if (accumulate(begin(vl), end(vl), 0) != a) continue;
        if (accumulate(begin(vr), end(vr), 0) != b) continue;
        cout << "yes" << '\n';
        for (int i = 0; i < n; i++) {
            cout << h[i] << " \n"[i+1==n];
        }
        return 0;      
    } while (next_permutation(begin(h), end(h)));

    cout << "no" << '\n';
}
