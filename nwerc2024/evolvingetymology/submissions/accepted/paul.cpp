#include <bits/stdc++.h>
using namespace std;
using i64 = long long;

int main() {
    int n; cin >> n;
    i64 k; cin >> k;

    i64 x = 1, a = 2;
    for (; k > 0; k /= 2) {
        if (k%2 == 1) x = a*x % n;
        a = a*a % n;
    }

    string s; cin >> s;
    for (int i = 0; i < n; i++) {
        cout << s[i*x % n];
    }
    cout << '\n';
}
