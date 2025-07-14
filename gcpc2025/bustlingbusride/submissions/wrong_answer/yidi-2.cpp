#include <bits/stdc++.h>
using namespace std;
using ll = long long;
#define all(x) ::begin(x), ::end(x)
void _d(auto... x) { ((cerr << ' ' << x), ...) << endl; }
#define debug(x...) cerr << "["#x"]:", _d(x)

int main() {
    cin.tie(0)->sync_with_stdio(0);

    int n, b, delay, w;
    cin >> n >> b >> delay >> w;
    vector<int> a(b);
    for (int& e : a) cin >> e;
    for (int i = 1; i < b; i++) a[i] += a[i-1];
    vector<int> c(n);
    for (int& e : c) cin >> e, e--;

    constexpr ll INF = 2e18;
    ll l = 0, r = INF;
    vector<int> mp(b);
    while (l+1 < r) {
        ll mid = (l+r) / 2;
        int ptr = 0;
        for (int bus=0; ptr<n; bus++) {
            ll t = (ll)bus*delay;
            if (t + 2*w + c[ptr] > mid) break;

            int mx = 0, cnt = 0;
            while (ptr < n) {
                int x = a[c[ptr]];
                mx = max(mx, x);
                t += (ll)(cnt - mp[c[ptr]]) * w * 2;
                t += 2*w;
                if (t + mx > mid) break;
                mp[c[ptr]]++;
                ptr++, cnt++;
            }
            for (int i=1; i<=cnt; i++) mp[c[ptr-i]]--;
        }
        if (ptr < n) l = mid;
        else r = mid;
    }
    cout << r << '\n';
}
