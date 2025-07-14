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


int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);
    ll n, x, y;
    ll maxx = 0;
    ll minx = (ll) 1e9;
    ll maxy = 0;
    ll miny = (ll) 1e9;
    cin >> n;
    for0(i, n) {
        cin >> x >> y;
        minx = min(minx, x);
        maxx = max(maxx, x);
        miny = min(miny, y);
        maxy = max(maxy, y);
    }
    cout << 4 << endl;
    cout << minx << " " << miny << endl;
    cout << maxx << " " << miny << endl;
    cout << maxx << " " << maxy << endl;
    cout << minx << " " << maxy << endl;
}