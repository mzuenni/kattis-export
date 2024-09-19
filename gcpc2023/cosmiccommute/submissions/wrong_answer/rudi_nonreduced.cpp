#include<bits/stdc++.h>

using namespace std;

const int MAXN = 3000000;
const int oo = 5000000;

int fromStart[MAXN];
int toEnd[MAXN];
vector<int> wormholes;
vector<int> adj[MAXN];
queue<int> q;
int n, m, k;

void bfs(int start, int * dist){
    q.push(start);
    dist[start] = 0;
    while(!q.empty()){
        int cur  = q.front();
        q.pop();

        for(int nb : adj[cur]){
            if(dist[nb] < oo) continue;
            dist[nb] = dist[cur] + 1;
            q.push(nb);
        }
    }
}

long long gcd(long long a, long long b) {
    if (a == 0) return b;
    return gcd(b % a, a);
}

int main(){
    cin >> n >> m >> k;
    for(int i=0; i<n; i++) fromStart[i] = oo;
    for(int i=0; i<n; i++) toEnd[i] = oo;
    for(int i=0; i<k; i++){
        int a;
        cin >> a;
        wormholes.push_back(a-1);
    }
    for(int i=0; i<m; i++){
        int a, b;
        cin >> a >> b;
        adj[a-1].push_back(b-1);
        adj[b-1].push_back(a-1);
    }

    bfs(0, fromStart);
    bfs(n-1, toEnd);

   

    // expected cost starting at a random wormhole is sumOfAllCosts / k
    long long sumOfAllCosts = 0;
    for(int w : wormholes) sumOfAllCosts += toEnd[w];

    // going from start to end costs at most (k-1) * minCost
    long long minCost = (k-1) * fromStart[n-1];
    for(int w: wormholes){
        long long val = (k-1) * fromStart[w] + sumOfAllCosts - toEnd[w];
        minCost = min(minCost, val);
    }

    long long ggt = 1;
    cout << minCost / ggt << "/" << (k - 1) / ggt << endl;
}