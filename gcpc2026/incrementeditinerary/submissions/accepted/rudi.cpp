#include<bits/stdc++.h>
#include<cassert>
using namespace std;

const int MAXN = 300000;
vector<int> adj[MAXN];
int dist[2][MAXN];
const int oo = 0x3f3f3f3f;

void reject(){
    cout << "impossible" << endl;
    exit(0);
}

void accept(){
    cout << "possible" << endl;
    exit(0);
}

void bfs(int start, int dist[MAXN]){
    memset(dist, 0x3f3f3f3f, sizeof(int)*MAXN);
    queue<pair<int, int>> q;
    q.push({0, start});
    while(!q.empty()){
        auto [d, v] = q.front();
        q.pop();
        
        if(dist[v] < oo) continue;
        dist[v] = d;

        for(int u : adj[v]) if(dist[u] == oo) q.push({d+1, u});
    } 
}

int main(){
    int n, m;
    cin >> n >> m;
    for(int i = 0; i < m; i++){
        int u, v;
        cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    queue<pair<int, int>> q;
    q.push({0, n});

    bfs(1, &dist[0][0]);
    bfs(n, &dist[1][0]);

    assert(dist[0][n] == dist[1][1]);
    int d = dist[0][n];


    if(dist[0][n] == oo) reject();

    
    for(int u = 1; u <= n; u++) {
        assert(dist[0][u] + dist[1][u] >= d);
        if(dist[0][u] + dist[1][u] != d) continue;
        
        for(int v : adj[u]){
            if(dist[0][v] == dist[0][u]) accept();
            if(dist[1][v] == dist[1][u]) accept();
        }
    }
    reject();
}
