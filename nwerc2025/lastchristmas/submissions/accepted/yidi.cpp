#include <bits/stdc++.h>
using namespace std;
using ll = int64_t;
#define all(x) ::begin(x), ::end(x)
void _d(auto... x) { ((cerr << ' ' << x), ...) << endl; }
#define debug(x...) cerr << "["#x"]:", _d(x)

int main() {
    cin.tie(0)->sync_with_stdio(0);

    int n;
    cin >> n;
    map<string, array<int, 11>> mp;
    for (int i=0; i<n; i++) {
        for (int it=1; it<=10; it++) {
            string s;
            cin >> s;
            mp[s][0]++;
            mp[s][it]++;
        }
    }

    array<int, 11> best = {};
    string ans;
    for (auto [s, a] : mp) {
        if (a > best) best = a, ans = s;
        else if (a == best) ans = "tie";
    }

    cout << ans << '\n';
}
