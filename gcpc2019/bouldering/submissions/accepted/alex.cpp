#include <bits/stdc++.h>
using namespace std;

#define FOR(i,a,b) for (int i = (a); i < (b); i++)

string input[32];
vector<pair<int,long double> > adj[1024];
int cost[1024];
long double sqv[2048];
long double dists[16][1024];

int main(){
    FOR(i,0,2048)sqv[i] = sqrt((long double)i);
    int H, W, R, S;
    cin >> H >> W >> R >> S;
    FOR(h,0,H)cin >> input[h];
    int s = -1, f = -1;
    FOR(h,0,H)FOR(w,0,W)if(input[h][w] != '.'){
        f = h*W+w;
        if(s == -1)s = f;
    }
    FOR(i,0,H*W)adj[i].clear();
    FOR(h,0,H)FOR(w,0,W)if(input[h][w] != '.'){
        cost[h*W+w] = input[h][w] - '0';
        FOR(hh,max(0,h-R),min(H,h+R+1))FOR(ww,max(0,w-R),min(W,w+R+1)){
            int dh = hh-h, dw = ww-w;
            if(dh*dh+dw*dw > R*R)continue;
            if(input[hh][ww] == '.')continue;
            adj[h*W+w].push_back(make_pair(hh*W+ww, sqv[dh*dh+dw*dw]));
        }
    }
    int change = 0;
    S-=cost[f];
    const long double INF = 1e300;
    long double res = INF;
    FOR(i,0,16)FOR(j,0,H*W)dists[i][j] = INF;
    int cur = 0, last = 15;
    dists[0][s] = 0;
    while(change++ < 20 && S>=0){
        --S;
        res = min(res, dists[cur][f]);
        FOR(i,0,H*W){
            int tv = (cur + cost[i]) & 15;
            if(dists[cur][i] < dists[last][i]){
                change = 0;
                for(auto ed: adj[i]){
                    int to = ed.first;
                    dists[tv][to] = min(dists[tv][to], dists[cur][i] + ed.second);
                }
            } else {
                dists[cur][i] = dists[last][i];
            }
        }
        last = cur;
        cur = (cur + 1) & 15;
    }
    if(res > 1e200)cout << "impossible\n";
    else printf("%.9lf\n", (double)res);
    return 0;
}
