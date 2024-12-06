#include <bits/stdc++.h>
using namespace std;
using i64 = long long;

string step(string s) {
    int n = size(s);
    string t(n, ' ');
    for (int i = 0; i < n; i++) {
        t[i] = s[2*i % n];
    }
    return t;
}

int main() {
    int n; cin >> n;
    i64 k; cin >> k;

    string s; cin >> s;

    string t = step(s), h = step(t);
    while (t != h) {
        t = step(t);
        h = step(step(h));
    }

    int pre = 0;
    t = s;
    while (t != h) {
        t = step(t);
        h = step(h);
        pre++;
    }

    int cyc = 1;
    h = step(t);
    while (t != h) {
        h = step(h);
        cyc++;
    }

    k = k <= pre ? k : (pre + (k-pre) % cyc);
    while (k--) {
        s = step(s);
    }
    cout << s << '\n';
}

