#include <bits/stdc++.h>
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

bool check(vl ind, ll n, ll d) {
    ll close = 0;
    ll far = 0;
    ll i = 0;
    while (i < sz(ind)) {
        while (close < sz(ind) && ind[close] - ind[i] < d) close++;
        while (far < sz(ind) && ind[far] - ind[i] < 2 * d) far++;
        if (close != far) return false;
        i++;
    }
    return true;
}


int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);
    ll x, n, d;
    cin >> n >> d;
    vector<vl> ind(n + 1);
    for0(i, n) {
        cin >> x;
        ind[x].pb(i);
    }
    for0(i, n) {
        if (check(ind[i], n, d)) {
            cout << i << endl;
            return 0;
        }
    }
}