#include <bits/stdc++.h>
using namespace std;
using ll = long long;
#define all(x) ::begin(x), ::end(x)
void _d(auto... x) { ((cerr << ' ' << x), ...) << endl; }
#define debug(x...) cerr << "["#x"]:", _d(x)

int main() {
    cin.tie(0)->sync_with_stdio(0);

    string pass, s;
    int n;
    cin >> pass >> n >> s;

    if (pass == "Encode") {
        if (count(all(s), '1') == 0) cout << s << endl;
        else {
            for (int i=0; i<n; i++) {
                char c = s[i];
                s[i] = '2';
                if (c == '1') break;
            }
            cout << s << endl;
        }
    } else {
        assert(pass == "Decode");
        int ind = 0;
        for (; ind<n; ind++) {
            if (s[ind] != '2') continue;
            bool ok = true, cs = true;
            for (int j=1; j<n && ok; j++) {
                if (!cs && s[(ind + j) % n] == '2') ok = false;
                if (s[(ind + j) %n] != '2') cs = false;
            }
            if (ok) break;
        }
        rotate(s.begin(), s.begin()+ind, s.end());
        for (int i=0; i<n; i++) {
            if (s[i] == '2') {
                s[i] = '1';
                if (i != 0) s[i-1] = '0';
            } else {
                break;
            }
        }
        cout << s << '\n';
    }
}
