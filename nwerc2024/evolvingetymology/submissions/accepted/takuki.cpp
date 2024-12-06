#include <iostream>
#include <numeric>
#include <vector>
using namespace std;

vector<int> apply(vector<int> a, vector<int> b) {
    int n = int(a.size());
    vector<int> c(n);
    for (int i = 0; i < n; i++) {
        c[i] = b[a[i]];
    }
    return c;
}

int main() {
    long long n, k;
    cin >> n >> k;
    string s;
    cin >> s;
    vector<int> f(n);
    for (int i = 0; i < n; i++) {
        f[i] = (2 * i) % n;
    }
    vector<int> t(n);
    iota(t.begin(), t.end(), 0);
    for (int x = 0; (1L << x) <= k; x++) {
        if (k & (1L << x)) {
            t = apply(t, f);
        }
        f = apply(f, f);
    }
    for (int i = 0; i < n; i++) {
        cout << s[t[i]];
    }
    cout << '\n';
    return 0;
}
