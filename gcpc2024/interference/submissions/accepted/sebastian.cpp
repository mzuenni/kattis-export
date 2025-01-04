//
// Created by sebastian on 20.04.24.
//

#include "iostream"
#include "vector"
#include "tuple"

#define rep(a, b)   for(int a = 0; a < (b); ++a)
#define endl        '\n'

using namespace std;
using ll = long long;

int main() {
    int n; ll w;
    cin >> n >> w;

    vector<tuple<ll, ll, ll>> waves;
    vector<ll> results;

    rep(_, n) {
        char c;
        cin >> c;
        if (c == '!') {
            ll pos, length, ampl;
            cin >> pos >> length >> ampl;
            waves.emplace_back(pos, length, ampl);
        } else {
            ll pos;
            cin >> pos;
            ll cur = 0l;
            for (auto wave : waves) {
                auto [p, l, a] = wave;
                if (p <= pos && pos < p + l) {
                    if ((pos - p) % 2 == 1) continue;
                    if ((pos - p) % 4 == 2) cur -= a;
                    else cur += a;
                }
            }
            results.push_back(cur);
        }
    }
    // cout << results.size() << endl;
    for (ll out: results) cout << out << endl;

    return 0;
}
