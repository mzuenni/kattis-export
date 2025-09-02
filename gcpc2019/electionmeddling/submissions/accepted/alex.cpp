#include <bits/stdc++.h>
using namespace std;

#define all(c) (c).begin(), (c).end()
#define FOR(i,a,b) for (int i = (a); i < (b); i++)

int main(){
    int D,P;
    cin >> D >> P;
    vector<int> results;
    FOR(d,0,D){
        vector<int> v(P);
        FOR(p,0,P)cin >> v[p];
        int lo = 0, hi = 1024;
        while(lo < hi){
            int m = lo + (hi - lo) / 2;
            int need = 0;
            FOR(p,1,P)need += max(0, v[p] - m - v[0] +1);
            if(need > m)lo = m + 1;
            else hi = m;
        }
        results.push_back(lo);
    }
    sort(all(results));
    int res = 0;
    FOR(i,0,(D+2)/2)res += results[i];
    cout << res << endl;
    return 0;
}
