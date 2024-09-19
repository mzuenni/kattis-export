#include <bits/stdc++.h>

#define rep(a, b)   for(int a = 0; a < (b); ++a)
#define all(a)      (a).begin(),(a).end()
#define endl        '\n'

using namespace std;
using Graph = vector<vector<int>>;
using ll = long long;
ll INF = 1e18+5;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n,m,k;
    cin>>n>>m>>k;
    Graph adj(n);
    vector holes(k,0);
    rep(i,k) cin>>holes[i], --holes[i];
    rep(i,m) {
        int u,v; cin>>u>>v;
        --u,--v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    auto bfs = [&](int s) {
        vector dist(n,INF);
        vector done(n,false);
        queue<int> q{{s}};
        dist[s] = 0;
        while(size(q)) {
            int v = q.front(); q.pop();
            done[v] = true;
            for(int u : adj[v]) {
                if(done[u]) continue;
                dist[u] = min(dist[u], dist[v]+1);
                q.push(u);
            }
        }
        return dist;
    };

    auto ds = bfs(0);
    auto dt = bfs(n-1);

    ll sum_holes = 0;
    for(int h : holes) sum_holes += dt[h];

    // exp for h = ds[h] + (sum_holes-dt[h])/(k-1)
    // -> multiply all with (k-1)
    ll res = ds[n-1] * (k-1);
    for(int h : holes) res = min(res, ds[h] * (k-1) + sum_holes - dt[h]);

    auto g = gcd(res, k-1);
    cout << res/g << '/' << (k-1)/g << endl;

    return 0;
}
