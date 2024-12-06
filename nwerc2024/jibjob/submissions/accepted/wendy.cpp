#include <vector>
#include <iostream>
#include <cmath>

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

    ll n, x, y;
    cin >> n;
    vector<pl> pos(n);
    vl h(n);
    for0(i, n) {
        cin >> x >> y >> h[i];
        pos[i] = {x, y};
    }

    for0(i, n) {
        ll res = h[i];
        for0(j, n) {
            if (h[j] > h[i]) res = min(res, (ll) sqrt(pow(pos[i].first - pos[j].first, 2) + pow(pos[i].second - pos[j].second, 2)));
        }
        cout << res << endl;
    }
}