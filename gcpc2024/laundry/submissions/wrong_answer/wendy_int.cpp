#include <bits/stdc++.h>
#define f(i, s, k, l) for (int i = s; i < k; i += l)
#define for0(i, k) f(i, 0, k, 1)

#define pl pair<long long, long long>
#define pb push_back
#define vl vector<int>
#define vi vector<int>
#define sz(x) (ll)(x).size()

using namespace std;
using ll = int;
using ld = long double;

ll k;   

ll greedy(vl wash, vl doubles, ll i, ll abc) {
    wash[i] += doubles[0]; // put AB completely in A or in B (try both)
    for0(j, 2) {
        ll r = (k - (wash[j] % k)) % k; 
        wash[j] += min(r, doubles[2 - j]); // fill A (B) (to multiple of k) using AC (BC)
        wash[2] += doubles[2 - j] - min(r, doubles[2 - j]); // put rest of AC (BC) into C 
        ll add = min((k - (wash[j] % k)) % k, abc); 
        wash[j] += add; 
        abc -= add; 
    }
    wash[2] += abc; 
    ll res = 0; 
    for0(i, 3) res += wash[i] / k + (wash[i] % k != 0);
    return res; 
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    
    ll t; 
    cin >> t; 

    while (t--) {
        ll abc; 
        cin >> k; 
        vl wash(3), doubles(3);
        for0 (i, 3) cin >> wash[i]; 
        for0 (i, 3) cin >> doubles[i];
        cin >> abc;   

        ll bestWash = (ll) (9 * 1e9); 

        for0 (i, 3) {
            for0 (j, 2) bestWash = min(greedy(wash, doubles, j, abc), bestWash); 
            rotate(wash.begin(), wash.begin() + 1, wash.end()); 
            rotate(doubles.begin(), doubles.begin() + 1, doubles.end()); 
        }
        cout << bestWash << endl; 
    }
    
}