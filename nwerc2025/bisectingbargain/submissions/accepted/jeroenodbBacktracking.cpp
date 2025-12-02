#pragma GCC optimize("O3")
#include "bits/stdc++.h"
using namespace std;

typedef vector<int> vi;
typedef vector<vi> vvi;
typedef pair<int,int> pi;
const int oo = 1e9;

void solve(int n) {
    vi num =    {500,200,100,50,20,10,5,2,1};
    vi atmost = {999,999,  1, 1, 5, 1,1,5,1};
    vi ans;
    typedef bitset<5001> DP;
    int iter=0;
    auto rec = [&](auto&& self, int at,int left, DP bs) {
        if(n%2==0 and bs[n/2]) return false;
        if(at==size(num)) {
            return left==0;
        }
        vi check;
        vector<DP> dp = {bs};
        int mn = min(left/num[at],atmost[at]);
        for(int i=0;i<mn;++i) {
            dp.push_back(dp.back()|dp.back()<<num[at]);
        }
        for(int take=mn;take>=0;--take) {

            
            if(self(self,at+1,left-take*num[at],dp[take])) {
                for(int j=0;j<take;++j) ans.push_back(num[at]);
                return true;
            }
            if(num[at]==1) break;
        }
        return false;
    };
    bitset<5001> bs;
    bs[0]=1;

    if(!rec(rec,0,n,bs)) {
        cout << "splittable\n";
        cout << '\n';
    } else {
        // cout << "unsplittable\n";
        cout << size(ans);
        for(auto x : ans) cout << ' ' << x;
        cout << '\n';
    }
}

int main() {
    // for(int n=1;n<=10000;++n) {
    //     cerr << n << '\n';
    //     solve(n);
    // }
    int n; cin >> n;
    solve(n);
}