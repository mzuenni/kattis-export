#include<bits/stdc++.h>
using namespace std;
typedef long long ll;

int main() {
    ll n, m, q, idx, d, t, w;
    cin >> n >> m;
    priority_queue<tuple<ll, ll, ll>> eq;
    for (ll i = 0; i < m; ++i) {
        cin >> idx >> d >> t;
        eq.emplace(t, d, idx - 1);
    }
    cin >> q;
    priority_queue<pair<ll, ll>> qq;
    for (ll i = 0; i < q; ++i) {
        cin >> w;
        qq.emplace(w, i);
    }
    ll l = n * 10000000, res = (n - 1) * l, ds[n - 1], qr[q];
    for (ll i = 0; i < n - 1; ++i) ds[i] = l;
    while (!qq.empty()) {
        auto [w, qi] = qq.top();
        qq.pop();
        qr[qi] = l;
        while (!eq.empty() && get<0>(eq.top()) >= w) {
            auto [t, d, i] = eq.top();
            eq.pop();
            if (d < ds[i]) {
                res -= ds[i] - d;
                ds[i] = d;
                qr[qi] = res;
            }
        }
        l = qr[qi];
    }
    for (ll i = 0; i < q; ++i) {
        if (qr[i] > (n - 1) * 1000000) cout << "impossible" << endl;
        else cout << qr[i] << endl;
    }
    return 0;
}
