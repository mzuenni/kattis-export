#include <bits/stdc++.h>
using namespace std;
using ll = long long;
#define all(x) ::begin(x), ::end(x)
void _d(auto... x) { ((cerr << ' ' << x), ...) << endl; }
#define debug(x...) cerr << "["#x"]:", _d(x)

int main() {
    cin.tie(0)->sync_with_stdio(0);

    int n;
    cin >> n;
    string s = "!Aa01234";
    sort(all(s));

    while (n--) {
        cout << s << '\n';
        next_permutation(all(s));
    }
}
