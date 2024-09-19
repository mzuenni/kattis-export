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

vl bfs(vector<vl> &adj, ll start) {
    vl dist(sz(adj), -1);
    queue<ll> q;
    q.push(start);
    dist[start] = 0;
    while(!q.empty()) {
        ll v = q.front();
        q.pop();
        for(ll next : adj[v]) {
            if(dist[next] != -1) continue;
            dist[next] = dist[v] + 1;
            q.push(next);
        }
    }
    return dist;
}

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);

    ll n, m, k, a, b;
    cin >> n >> m >> k;
    vl wormholes(k);
    for0(i, k) {
        cin >> wormholes[i];
        wormholes[i]--;
    }
    vector<vl> adj(n);
    for0(i, m) {
        cin >> a >> b;
        a--;
        b--;
        adj[a].pb(b);
        adj[b].pb(a);
    }

    vl d1 = bfs(adj, 0);
    vl d2 = bfs(adj, n - 1);

    ll sumToTarget = 0;
    for(ll w : wormholes) sumToTarget += d2[w];

    sort(wormholes.begin(), wormholes.end(), [&](ll a, ll b) {
        return d1[a] < d1[b];
    });
    while(sz(wormholes) > 10'000) wormholes.pop_back();

    ll best = (k-1)*d1[n - 1];
    for(ll w : wormholes) best = min(best, (k-1)*d1[w] + sumToTarget - d2[w]);

    ll g = gcd(best, k-1);
    cout << best/g << "/" << (k-1)/g << endl;
}