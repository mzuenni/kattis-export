#include <iostream>
#include <vector>
#include <assert.h>

using namespace std;
using ll = long long;

ll n, t;
vector<ll> naive(vector<ll> a, ll k = t) {
    for (ll i = 0; i < k; i++) {
        ll stones = 1;
        for (ll j = 0; j < n; j++) {
            stones--;
            a[j]++;
            if (stones == 0) {
                if (a[j] == 1) break;
                stones = a[j];
                a[j] = 0;
            }
        }
    }
    return a;
}

vector<ll> faster(vector<ll> a) {
    ll k = t;
    for (ll i = 2, h = 1; true; i *= 2, h++) {
        if (a[0] != 0) a = naive(a, 1);
        else k++;
        for (ll j = 2*h; j < n; j += 2) if (a[j] == 0 && i < (1LL << 35)) {
            h++;
            i *= 2;
        } else {
            break;
        }
        if (k > i) {
            k -= i;
            for (ll j = 0; j < h && 2*j < n; j++) {
                a[2*j] = 1;
                if (2*j+1 != n)
                    a[2*j+1] += (1LL << (h-j-1)) - 1;
            }
        } else {
            ll s = (--k >> 1);
            for (ll j = 0; j < h && 2*j < n; j++) {
                a[2*j] = ((1LL << j) & k) > 0;
                if (2*j+1 != n)
                    a[2*j+1] += s;
                s >>= 1;
            }
            break;
        }
    }
    return a;
}

int main() {
    cin.tie(0);
    ios_base::sync_with_stdio(0);

    cin >> n >> t;
    vector<ll> a(n);
    for (auto &k: a) cin >> k;

    vector<ll> res = faster(a);
    if (t <= 10) {
        vector<ll> res_n = naive(a);
        assert (res == res_n);
    }
    for (ll i = 0; i < n; i++) cout << res[i] << " \n"[i+1 == n];

    return 0;
}