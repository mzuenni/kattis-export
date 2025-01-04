#include <vector>
#include <iostream>
#include <algorithm>
#include <cstring>
using namespace std;

const int MAXN = 500000;
vector<int> adj[MAXN];
bool vis[MAXN];

int dfs(int i, int num){
    if(vis[i]) return num;
    vis[i] = true;
    num++;
    for(int nb: adj[i]) num = dfs(nb, num);
    return num;
}

int main(){
    int n, m;
    cin >> n >> m;

    for(int i = 0; i < m; i++){
        int a, b;
        cin >> a >> b;
        adj[a].push_back(b);
        adj[b].push_back(a);
    }

    memset(vis, 0, sizeof(vis));
    int res = 1;
    for(int i=1; i<=n; i++) {
        if(vis[i]) continue;
        res = max(res, dfs(i, 0));
    }

    cout << res << endl;
}

