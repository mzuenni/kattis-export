#include <bits/stdc++.h>
using namespace std;
using ll = long long;
#define all(x) ::begin(x), ::end(x)
void _d(auto... x) { ((cerr << ' ' << x), ...) << endl; }
#define debug(x...) cerr << "["#x"]:", _d(x)

int main() {
    cin.tie(0)->sync_with_stdio(0);

    int n, a, b;
    cin >> n >> a >> b;

    if ((n != 1 && a == 1 && b == 1) || a+b > n+1) cout << "No\n";
    else {
        vector<int> ans(n);
        iota(ans.begin(), ans.end(), 1);

        if (b > 1) {
            a--, b--;
            reverse(ans.begin() + a, ans.end());
            reverse(ans.begin() + a + b, ans.end());
        } else {
            a--;
            reverse(ans.begin(), ans.end() - a);
        }
        cout << "Yes\n";
        for (int e : ans) cout << e << ' ';
        cout << '\n';
    }
}
