#include <vector>
#include <iostream>

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

vl mult(vl &a, vl &b) {
    vl res;
    for0(i, sz(a)) res.pb(a[b[i]]);
    return res;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    ll n, k;
    string s;
    cin >> n >> k >> s;
    vl order;
    for0(i, (n + 1) / 2) order.pb(2 * i);
    for0(i, n / 2) order.pb(2 * i + (n % 2 != 0));
    vl res;
    for0(i, n) res.pb(i);
    while (k > 0) {
        if (k % 2 != 0) res = mult(res, order);
        order = mult(order, order);
        k /= 2;
    }
    for0(i, n) cout << s[res[i]];
    cout << endl;
}