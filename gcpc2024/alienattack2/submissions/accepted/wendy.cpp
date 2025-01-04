#include <vector>
#include <iostream>
#include <algorithm>
#include <queue>
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
    ll n, m, a, b; 
    cin >> n >> m; 

    vector<vl> adj(n);
    vector<bool> seen(n, false); 
    for0(i, m) {
        cin >> a >> b;
        adj[a - 1].pb(b - 1); 
        adj[b - 1].pb(a - 1);  
    }

    ll res = 0; 
    for0(i, n) {
        if (seen[i]) continue; 
        ll size = 0; 
        queue<ll> q; 
        q.push(i); 
        while (!q.empty()) {
            ll cur = q.front(); 
            q.pop(); 
            if (seen[cur]) continue;
            size++; 
            seen[cur] = true;  
            for(ll v: adj[cur]) {
                if (seen[v]) continue; 
                q.push(v); 
            }
        }
        res = max(res, size); 
    }

    cout << res << endl; 
}