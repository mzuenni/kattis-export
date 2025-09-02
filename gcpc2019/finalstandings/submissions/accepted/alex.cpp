#include <bits/stdc++.h>
using namespace std;
#define FOR(i,a,b) for (int i = (a); i < (b); i++)

long double strength[128], difficulty[128];
string scoreboard[128][128];
long double dp[128][128];
int main(){
    int T,P;
    cin >> T >> P;
    FOR(t,0,T-1)cin >> strength[t];
    FOR(p,0,P)cin >> difficulty[p];
    FOR(t,0,T)FOR(p,0,P)cin >> scoreboard[t][p];
    int solved = 0;
    FOR(p,0,P)solved += (scoreboard[T-1][p] == "X");
    long double res = 1;
    FOR(t,0,T-1){
        dp[0][0] = 1;
        FOR(p,0,P){
            FOR(k,0,p+2)dp[p+1][k] = 0;
            long double success;
            if(scoreboard[t][p] == "X")success = 1;
            else if(scoreboard[t][p] == "-")success = 0;
            else success = strength[t] * difficulty[p];
            long double failure = 1-success;
            FOR(k,0,p+1){
                dp[p+1][k+1] += dp[p][k] * success;
                dp[p+1][k] += dp[p][k] * failure;
            }
        }
        long double better = 0;
        FOR(p,solved+1,P+1)better += dp[P][p];
        res = res * (1-better);
    }
    printf("%.9lf\n", (double)res);
    return 0;
}
