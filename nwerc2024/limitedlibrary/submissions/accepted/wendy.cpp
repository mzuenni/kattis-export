#include <vector>
#include <iostream>
#include <algorithm>

#define f(i, s, k, l) for (int i = s; i < k; i += l)
#define for0(i, k) f(i, 0, k, 1)

#define pl pair<long long, long long>
#define pb push_back
#define vl vector<long long>
#define vi vector<int>
#define sz(x) (ll)(x).size()

using namespace std;
using ll = long long;
using ld = long double;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    ll n, m, w, old;
    cin >> n >> m >> w >> old;
    vl rack(n), book(m);
    for0(i, n) cin >> rack[i];
    for0(i, m) cin >> book[i];
    sort(rack.begin(), rack.end());
    sort(book.begin(), book.end());

    ll l = -1;
    ll r = n + 1;
    while (r - l > 1) {
        ll mid = (l + r) / 2;
        ll b = 0;
        for0(i, n) {
            ll cap = w;
            if (i < mid) cap = old;
            while (b < m && book[b] <= rack[i] && cap > 0) {
                b++;
                cap--;
            }
        }
        if (b == m) l = mid;
        else r = mid;
    }

    if (l == -1) cout << "impossible" << endl;
    else cout << l << endl;
}