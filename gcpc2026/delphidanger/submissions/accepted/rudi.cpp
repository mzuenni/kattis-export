#include<bits/stdc++.h>
using namespace std;

const int MAXN = 500000;
const int MAXM = 500000;
vector<int> adj[MAXN];
vector<pair<int, pair<int, int>>> prophecies;
set<int> cur_nodes;
set<pair<int, int>> cur_prophecies;


int root[MAXN];
int rnk[MAXN];
void uinit(int n){
    for(int i = 0; i < n+1; i++){
        root[i] = i;
        rnk[i] = 1;
    }
}
int ufind(int u){
    if(root[u] == u) return u;
    root[u] = ufind(root[u]);
    return root[u];
}
void uunite(int u, int v){
    int root_u = ufind(u);
    int root_v = ufind(v);
    if(root_u == root_v) return;
   
    if(rnk[root_u] < rnk[root_v]) swap(root_u, root_v);
    root[root_v] = root_u;
    rnk[root_u] += rnk[root_v];
}

int color[MAXN];
int risk_contributions[2];
bool dfs(int u, int col){
    if(color[u] == col) return true;
    if(color[u] == 1 - col) return false;
    color[u] = col;
    risk_contributions[col] += rnk[u];
    for(int v : adj[u]) if(!dfs(v, 1 - col)) return false;
    return true;
}
long long is_bipartite(){
    for (int v: cur_nodes) color[v] = -1;
    long long risk = 0;
    for(int v : cur_nodes){
        if(color[v] == -1){
            risk_contributions[0] = risk_contributions[1] = 0;
            if(!dfs(v, 0)) return -0x3f3f3f3f;
            risk += min(risk_contributions[0], risk_contributions[1]);
        }
    }
    return risk;
}


int main(){
    int n, m;
    cin >> n >> m;

    for(int i = 0; i < m; i++){
        int u, v, t;
        cin >> u >> v >> t;
        prophecies.push_back({t, {u, v}});
    }

    sort(prophecies.begin(), prophecies.end());

    long long risk = 0;
    uinit(n);
    for(int i = prophecies.size() - 1; i >= 0;){
        auto [t, _] = prophecies[i];
        //cout << "t = " << t << endl;


        for(;i >= 0 && prophecies[i].first == t; i--){
            auto [_, p] = prophecies[i];
            auto [u, v] = p;

            //cout << "u = " << u << ", v = " << v << endl;
            //cout << "  root_u = " << ufind(u) << ", root_v = " << ufind(v) << endl;
            
            int root_u = ufind(u);
            int root_v = ufind(v);
            adj[root_u].push_back(root_v);
            adj[root_v].push_back(root_u);
            cur_nodes.insert(root_u);
            cur_nodes.insert(root_v);
            cur_prophecies.insert({root_u, root_v});
        }
        //cout << "  |cur_prophecies| = " << cur_prophecies.size() << endl;

        risk += is_bipartite();
        for(auto [u, v] : cur_prophecies) uunite(u, v);


        for(int u: cur_nodes) adj[u].clear();
        cur_nodes.clear();
        cur_prophecies.clear();


    }
    
    if(risk < 0){
        cout << "impossible" << endl;
    } else {
        cout << "possible" << endl;
        cout << risk << endl;
    }
}