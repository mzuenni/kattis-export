#include <bits/stdc++.h>
using namespace std;
using ll = long long;
#define all(x) ::begin(x), ::end(x)
void _d(auto... x) { ((cerr << ' ' << x), ...) << endl; }
#define debug(x...) cerr << "["#x"]:", _d(x)

int main() {
    cin.tie(0)->sync_with_stdio(0);

    int n, m;
    cin >> n >> m;
    int cnt = 0;
    for (int i=0; i<n; i++) {
        string s;
        cin >> s;
        cnt += count(all(s), '#');
    }

    for (int i=n; i>0; i--) {
        if (cnt % (i*i) == 0) {
            cout << i << '\n';
            return 0;
        }
    }
}
