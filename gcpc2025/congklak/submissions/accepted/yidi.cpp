#include <bits/stdc++.h>
using namespace std;
using ll = long long;
#define all(x) ::begin(x), ::end(x)
void _d(auto... x) { ((cerr << ' ' << x), ...) << endl; }
#define debug(x...) cerr << "["#x"]:", _d(x)

int main() {
    cin.tie(0)->sync_with_stdio(0);

    ll n, t;
    cin >> n >> t;
    vector<ll> a(n);
    for (ll& e : a) cin >> e;
    for (int i=0; i<n && t > 0; i+=2) {
        if (a[i]) {
            a[i]++;
            t--;
            int ptr = i;
            while (ptr < n && a[ptr] > 1) {
                ll x = min(a[ptr], n-ptr);
                a[ptr] = 0;
                for (int it=0; it<x; it++) {
                    ptr++;
                    if (ptr < n) a[ptr]++;
                }
            }
        }

        a[i] = t%2;
        t /= 2;
        if (i+1 < n) a[i+1] += t;
    }

    for (ll e : a) cout << e << ' ';
    cout << '\n';
}
