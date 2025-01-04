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
 
ll eff(vl &diffs, ll val) {
    ll res = 0; 
    for0(i, sz(diffs)) res += abs(val + i - diffs[i]); 
    return res; 
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    ll n, t; 
    cin >> n; 
    vl diffs(n); 

    for0(i, n) cin >> diffs[i]; 

    ll l = (ll) -300000;
    ll r = (ll) 300000; 
    while (l < r - 1) {
        ll m1 = (l + r) / 2; 
        ll m2 = (l + r) / 2 + 1; 

        if (eff(diffs, m1) > eff(diffs, m2)) l = m1; 
        else r = m2;  
    } 
    cout << eff(diffs, r) << endl; 
}