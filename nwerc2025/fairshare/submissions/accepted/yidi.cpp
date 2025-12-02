#include <bits/stdc++.h>
using namespace std;
using ll = long long;
#define all(x) ::begin(x), ::end(x)
void _d(auto... x) { ((cerr << ' ' << x), ...) << endl; }
#define debug(x...) cerr << "["#x"]:", _d(x)

int main() {
    int n;
    cin >> n;

    vector<int> a(n), b(n);
    for (int i=0; i<n; i++) cin >> a[i] >> b[i];

    int actual = accumulate(a.begin(), a.end(), 0);
    int bill = accumulate(b.begin(), b.end(), 0);
    int best = -1, mn = 2e9;

    for (int i=0; i<n; i++) {
        int pays = bill - (actual - a[i]);
        if (pays > b[i]) continue;

        int diff = b[i] - pays;
        if (diff < mn) {
            mn = diff;
            best = i;
        }
    }

    if (best == -1) cout << "impossible" << endl;
    else cout << best+1 << endl;
}
