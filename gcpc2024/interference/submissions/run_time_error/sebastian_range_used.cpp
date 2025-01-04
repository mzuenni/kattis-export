//
// Created by sebastian on 20.04.24.
//

#include "vector"
#include "iostream"

#define rep(a, b)   for(int a = 0; a < (b); ++a)
#define endl        '\n'

using namespace std;
using ll = long long;
using vl = vector<ll>;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.precision(10);

    int n; ll w;
    cin >> n >> w;

    vl range(w+5, 0); // might also throw a bad_alloc runtime error here -> 10^9 Byte entries are GB sized, can be problematic
    vl results;

    rep(z, n) {
        char c;
        cin >> c;
        if (c == '!') {
            ll pos, length, ampl;
            cin >> pos >> length >> ampl;
            for (ll i = 0; i < length; i ++) {
                if (i % 2 == 0)
                    range[pos + i] += ampl * (1 - 2*(i % 4 == 2));
            }
        } else {
            ll pos;
            cin >> pos;
            results.push_back(range[pos]);
        }
    }
    // cout << results.size() << endl;
    for (ll out: results) cout << out << endl;

    return 0;
}
