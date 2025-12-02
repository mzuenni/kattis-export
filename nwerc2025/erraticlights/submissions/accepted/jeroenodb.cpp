#include "bits/stdc++.h"
using namespace std;
/*
This solution is O(n^3 * log(n)) (with some high polynomial dependence on k)
*/
int main() {
    int n; string s; cin >> n >> s;
    typedef array<int,3> S;
    S a{};
    string colours = "rgb";
    for(char c:s) {
        a[colours.find(c)]++;
    }
    
    map<S,double> dp;
    struct el {
        double d;
        S my;
        bool operator<(const el& o) const {
            return d>o.d;
        }

    };
    map<pair<S,int>,int> cnt;
    map<pair<S,int>,double> sumev;
    priority_queue<el> pq;
    auto push = [&](S s, double v) {
        pq.push({v,s});
    };

    push(S{0,0,n},0);
    push(S{0,n,0},0);
    push(S{n,0,0},0);
    while(!pq.empty())  {
        auto e = pq.top(); pq.pop();
        if(dp.count(e.my)) continue;
        if(e.my==a) {
            cout << setprecision(15) << e.d << '\n';
            break;
        }
        dp[e.my]=e.d;
        for(int x=0;x<3;++x) for(int y=0;y<3;++y) {
            auto nw = e.my;
            if(nw[x]) {
                nw[x]--;
                nw[y]++;
                if(!dp.count(nw)) {
                    auto& res = ++cnt[{nw,y}];
                    sumev[{nw,y}]+=e.d;
                    push(nw,sumev[{nw,y}]/res + 3./res);
                }
            }
        }
    }
    

}