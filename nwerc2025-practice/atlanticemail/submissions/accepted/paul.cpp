#include <bits/stdc++.h>
using namespace std;

int main() {
    string pass; cin >> pass;
    if (pass == "send") {
        int n; cin >> n;
        string s; cin >> s;
        for (int i = 0; i < 5; i++) {
            for (int j = 0; j < n; j++) {
                cout << ((s[j] >> i) & 1);
            }
            cout << string(i, '0') << '\n';
        }
    } else {
        vector<string> v(5);
        for (string &s: v) cin >> s;
        sort(begin(v), end(v), [&](string s, string t) { return s.size() < t.size(); });
        int n = v[0].size();
        string s(n, 96);
        for (int i = 0; i < 5; i++) {
            for (int j = 0; j < n; j++) {
                s[j] |= (v[i][j]-'0') << i;
            }
        }
        cout << s << '\n';
    }
}
