#include <bits/stdc++.h>
using namespace std;

int var(const string &s) {
    if (ssize(s) > 1) return -1;
    char c = s[0];
    if (!isalpha(c)) return -1;
    return islower(c) ? c-'a' : 26+c-'A';
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    int n; cin >> n;
    vector<string> a(n);
    for (string &s: a) cin >> s;

    int q; cin >> q;
    while (q--) {
        int k; cin >> k;
        vector<string> b(k);
        for (string &s: b) cin >> s;

        auto match = [&](int i) {
            vector<int> p(52, -1), q(52, -1);
            for (int j = 0; j < k; j++) {
                int va = var(a[i+j]), vb = var(b[j]);
                if ((va < 0) != (vb < 0)) return false;
                if (va >= 0) {
                    if (p[va] == -1) p[va] = vb;
                    if (p[va] != vb) return false;
                    if (q[vb] == -1) q[vb] = va;
                    if (q[vb] != va) return false;
                } else {
                    if (a[i+j] != b[j]) return false;
                }
            }
            return true;
        };

        bool res = false;
        for (int i = 0; i+k <= n; i++) {
            if (match(i)) {
                res = true;
                break;
            }
        }
        cout << (res ? "yes" : "no") << '\n';
    }
}
