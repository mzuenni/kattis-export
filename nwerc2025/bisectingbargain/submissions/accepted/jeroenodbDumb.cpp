#pragma GCC optimize("O3")
#include "bits/stdc++.h"
using namespace std;

typedef vector<int> vi;
typedef vector<vi> vvi;
typedef pair<int,int> pi;
const int oo = 1e9;

void solve(int n) {
    vi num =    {500,200,100,50,20,10,5,2,1};
    vi atmost = {999,999,  1, 1, 4, 1,1,4,1};
    vi ans;
    typedef vector<bool> DP;
    vi coins;
    auto check = [&]() {
        if(n%2==1) return true;
        DP dp(n/2+1);
        dp[0]=1;
        for(int c : coins) {
            for(int j=n/2-c;j>=0;--j) {
                if(dp[j]) {
                    dp[j+c]=1;
                }
            }
        }
        return !dp[n/2];
    };
    auto rec = [&](auto&& self, int at,int left) {
        if(at==size(num)) {
            if(left==0) {
                if(check()) {
                    ans=coins;
                    return true;
                } else {
                    return false;
                }
            }
            return false;
        }
        int cur=size(coins);
        for(int take=0;take<=atmost[at] and take*num[at]<=left;++take) {
            if(self(self,at+1,left-take*num[at])) {
                return true;
            }
            coins.push_back(num[at]);

        }
        coins.resize(cur);
        return false;
    };

    if(!rec(rec,0,n)) {
        cout << "splittable\n";
    } else {
        cout << size(ans);
        for(auto x : ans) cout << ' ' << x;
        cout << '\n';
    }
}

int main() {
    int n; cin >> n;
    solve(n);
}