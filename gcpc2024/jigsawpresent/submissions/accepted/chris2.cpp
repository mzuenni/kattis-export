#include <bits/stdc++.h>

#define rep(a, b)   for(int a = 0; a < (b); ++a)
#define all(a)      (a).begin(),(a).end()
#define endl        '\n'

using namespace std;
using Graph = vector<vector<int>>;
using ll = long long;

auto brute(const vector<pair<int,int>>& pieces) {
    int n = (int)size(pieces);
    auto sum = [&](int mask) {
        int x=0, y=0;
        rep(i,14) if(mask & (1<<i)) {
            auto [a,b] = pieces[i];
            x+=a; y+=b;
        }
        return pair(x,y);
    };

    vector<array<int,4>> diffs;
    rep(mask,1<<n) {
        auto [tx,ty] = sum(mask);
        for(int sub=mask; ; sub=(sub-1)&mask) {
            auto [sx,sy] = sum(sub);
            diffs.push_back({2*sx-tx,2*sy-ty,mask,sub});
            if(sub==0) break;
        }
    }
    return diffs;
}


int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.precision(10);

    // input
    int n; cin>>n;
    n = min(n,28); // don't care about large n
    vector arr(n, pair(0,0));
    for(auto& [a,b] : arr) cin>>a>>b;

    // meet in the middle
    auto n2 = n/2;
    if(n>20) n2 = 14;
    auto mid = begin(arr) + n2;
//    auto diffs1 = brute({begin(arr), mid});
    auto diffs2 = brute({mid, end(arr)});
    sort(all(diffs2));

    auto sum = [&](int mask) {
        int x=0, y=0;
        rep(i,n2) if(mask & (1<<i)) {
            auto [a,b] = arr[i];
            x+=a; y+=b;
        }
        return pair(x,y);
    };

    rep(mask,1<<n2) {
        auto [tx,ty] = sum(mask);
        for(int sub=mask; ; sub=(sub-1)&mask) {
            auto [sx,sy] = sum(sub);
            auto x = 2*sx-tx;
            auto y = 2*sy-ty;

            auto it = lower_bound(all(diffs2), array{-x,-y,0,0});
            if(it==end(diffs2)) {
                if(sub==0) break;
                continue;
            }
            auto [x2,y2,mask2,sub2] = *it;
            if(x2!=-x || y2!=-y) {
                if(sub==0) break;
                continue;
            }
            if(mask==0 && mask2==0) {
                if(sub==0) break;
                continue;
            }

            // build output
            vector<int> p1,p2;
            rep(i,28) {
                if((1<<i)&sub) p1.push_back(i);
                else if((1<<i)&mask) p2.push_back(i);
                if((1<<i)&sub2) p1.push_back(i+n2);
                else if((1<<i)&mask2) p2.push_back(i+n2);
            }

            // print output
            cout << "NO" << endl;
            cout << size(p1);
            for(auto e : p1) cout << ' ' << e+1;
            cout << endl;
            cout << size(p2);
            for(auto e : p2) cout << ' ' << e+1;
            cout << endl;
            return 0;
        }
    }

    cout << "YES" << endl;

    return 0;
}
