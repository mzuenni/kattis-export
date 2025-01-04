#include <bits/stdc++.h>

#define rep(a, b)   for(int a = 0; a < (b); ++a)
#define all(a)      (a).begin(),(a).end()
#define endl        '\n'

using namespace std;
using Graph = vector<vector<int>>;
using ll = long long;

const auto ZERO = 16*4'100;
map<int,pair<int,int>> diffs[2*ZERO];
vector<pair<int,int>> arr;

auto total(int mask) {
    int tx=0, ty=0;
    rep(i,size(arr)) if(mask&(1<<i)) {
        auto [a,b] = arr[i];
        tx+=a; ty+=b;
    }
    return pair(tx,ty);
}

template<class F>
auto iter_rec(int mask, F&& f, int bit=0, int sub=0, int sx=0, int sy=0) {
    if(bit==size(arr)) { f(sub,sx,sy); return; }
    auto [bx, by] = arr[bit];
    iter_rec(mask, f, bit+1, sub, sx, sy);
    if(mask&(1<<bit))
        iter_rec(mask, f, bit+1, sub | (1<<bit), sx+bx, sy+by);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.precision(10);

    // input
    int n; cin>>n;
    n = min(n,28); // don't care about large n
    vector input(n,pair(0,0));
    for(auto& [a,b] : input) cin>>a>>b;

    // meet in the middle
    auto n2 = n/2;
    arr = vector(begin(input)+n2, end(input));
    rep(mask, 1<<size(arr)) {
        auto [tx,ty] = total(mask);
        iter_rec(mask,[&] (int sub, int sx, int sy) {
            auto x = 2*sx-tx, y = 2*sy-ty;
            diffs[x+ZERO][y] = {mask,sub};
        });
    }

    arr = vector(begin(input), begin(input)+n2);
    rep(mask,1<<size(arr)) {
        auto [tx,ty] = total(mask);
        iter_rec(mask, [&](int sub, int sx, int sy) {
            auto x = 2*sx-tx, y = 2*sy-ty;
            auto& map = diffs[-x+ZERO];
            if(empty(map)) return;
            auto it = map.find(-y);
            if (it==end(map)) return;
            auto [mask2, sub2] = it->second;
            if (mask==0 && mask2==0) return;
            // build output
            vector<int> p1, p2;
            rep(i, 28) {
                if ((1 << i) & sub) p1.push_back(i);
                else if ((1 << i) & mask) p2.push_back(i);
                if ((1 << i) & sub2) p1.push_back(i + n2);
                else if ((1 << i) & mask2) p2.push_back(i + n2);
            }
            // print output
            cout << "NO" << endl;
            cout << size(p1);
            for (auto e: p1) cout << ' ' << e + 1;
            cout << endl;
            cout << size(p2);
            for (auto e: p2) cout << ' ' << e + 1;
            cout << endl;
            exit(0);
        });
    }

    cout << "YES" << endl;

    return 0;
}
