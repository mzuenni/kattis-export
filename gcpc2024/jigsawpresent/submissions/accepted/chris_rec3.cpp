
// freopen("../../test.in", "r", stdin);

#include <bits/stdc++.h>

#define rep(a, b)   for(int a = 0; a < (b); ++a)
#define all(a)      (a).begin(),(a).end()
#define endl        '\n'

using namespace std;
using Graph = vector<vector<int>>;
using ll = long long;

template<class F>
auto iter_masks(const vector<pair<int,int>>& arr, F&& f) {
    auto iter_rec = [&arr](auto&& self, auto&& f, int bit, int maskL, int maskR, int dx, int dy) -> void {
        if(bit>=0) {
            auto [x,y] = arr[bit];
            self(self, f, bit-1, maskL, maskR, dx, dy);
            self(self, f, bit-1, maskL|(1<<bit), maskR, dx+x, dy+y);
            self(self, f, bit-1, maskL, maskR|(1<<bit), dx-x, dy-y);
            return;
        }
        f(maskL, maskR, dx, dy);
    };
    iter_rec(iter_rec,f,size(arr)-1, 0,0,0,0);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.precision(10);

    // input
    int n; cin>>n;
    vector arr(n, pair(0, 0));
    n = min(n,28); // don't care about large n
    for(auto& [a,b] : arr) cin >> a >> b;

    // meet in the middle
    auto n2 = n/2;
    if(n>20) n2 = 14;
    const auto ZERO = 15*4'100;
    vector<vector<array<int,3>>> diffs(2*ZERO);
    iter_masks({begin(arr), begin(arr) + n2}, [&](int maskL, int maskR, int dx, int dy) {
        diffs[dx+ZERO].push_back({dy,maskL,maskR});
    });
    for(auto& vec : diffs) sort(all(vec));

    iter_masks({begin(arr) + n2, end(arr)}, [&](int maskL2, int maskR2, int dx, int dy) {
        auto& map = diffs[-dx+ZERO];
        if(empty(map)) return;
        auto it = lower_bound(all(map), array{-dy,0,0});
        if(it==end(map)) return;
        auto [dy2, maskL, maskR] = *it;
        if(dy != -dy2) return;
        if((maskL|maskR|maskL2|maskR2) ==0) return;

        // build output
        vector<int> p1, p2;
        rep(i, 28) {
            if(maskL&(1<<i)) p1.push_back(i);
            if(maskR&(1<<i)) p2.push_back(i);
            if(maskL2&(1<<i)) p1.push_back(i+n2);
            if(maskR2&(1<<i)) p2.push_back(i+n2);
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

    cout << "YES" << endl;

    return 0;
}
