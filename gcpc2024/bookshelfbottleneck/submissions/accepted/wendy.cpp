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

    ll n, h, x, y, z; 
    cin >> n >> h; 
    ll res = 0; 
    for0(i, n) {
        cin >> x >> y >> z; 
        vl a = {x, y, z};
        sort(a.begin(), a.end()); 
        if (a[0] > h) {
            cout << "impossible" << endl; 
            return 0; 
        } 
        if (a[1] <= h) res += a[0];
        else res += a[1];  
    }
    cout << res << endl; 
}