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

vl sol;
ll k, root;

ll dfs(ll v, vector<vl> &adj) {
    ll m = 0;
    for (ll c : adj[v]) m = max(m, dfs(c, adj));
    if (m == k - 1 || v == root) {
        sol.pb(v);
        return 0;
    }
    return m + 1;
}

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);

    ll n, p;
    cin >> n >> k;
    vector<vl> adj(n);
    for0(i, n - 1) {
        cin >> p;
        p--;
        adj[p].pb(i + 1);
    }

    dfs(0, adj);
    cout << sz(sol) << endl;
    for (ll x : sol) cout << x + 1 << endl;


}
