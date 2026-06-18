#include <bits/stdc++.h>
using namespace std;
using ll = int64_t;
#define all(x) ::begin(x), ::end(x)
#define debug(x...) [](auto&& ...y){ cerr << "["#x"]:"; ((cerr << ' ' << y), ...) << endl; }(x)

void NO() {
    cout << "no\n";
    exit(0);
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    int n;
    cin >> n;
    map<string, int> mp;
    for (int i=0; i<n; i++) {
        string s, t;
        cin >> s >> t;
        if (s[0] == 'p') {
            if (mp.count(t)) NO();
            mp[t] = 0;
        } else {
            if (!mp.count(t)) NO();
            mp[t]++;
        }
    }
    for (auto [x, y] : mp) if (y != 1) NO();
    cout << "yes\n";
}
