#pragma GCC optimize("O3")
#include <iostream>
#include <vector>
#include <random>
#include <array>
#include <algorithm>
using namespace std;
mt19937 rng(69);
int rnd(int l, int r) {
    return uniform_int_distribution(l,r)(rng);
}
long long sq(long long x) {
    return x*x;
}
int main() {
    int n; cin >> n;
    vector<int> a(n);
    for(auto& i : a) cin >> i,--i;
    vector<array<int,2>> ans;
    auto op = [&](int i, int j) {
        ans.push_back({i,j});
        vector<int> part(a.begin()+i,a.begin()+i+3);
        a.erase(begin(a)+i,begin(a)+i+3);
        a.insert(a.begin()+j,begin(part),end(part));
    };
    auto revert = [&]() {
        auto [i,j] = ans.back();
        ans.pop_back();
        op(j,i);
        ans.pop_back();
    };
    auto calc = [&]() {
        long long ans=0;
        for(int i=0;i<n;++i) {
            ans+=sq(a[i]-i)*sq(a[i]);
        }
        return ans;
    };
    int last = n;
    while(!is_sorted(begin(a),end(a))) {
        while(last>0 and a[last-1]==last-1) {
            --last;
        }

        
        long long bestnxt = calc();
        array<int,2> cur = {-1,-1};
        for(int x=0;x<10;++x) {
            int i = rnd(0,max(2,last-3));
            int j = rnd(0,max(2,last-3));
            op(i,j);

            auto nxt = calc()*(last>=10);
            if(nxt<bestnxt) {
                bestnxt = nxt;
                cur = {i,j};
            }
            revert();
        }
        if(cur[0]!=-1) {
            op(cur[0],cur[1]);
        }
    }

    cout << ans.size() << '\n';
    for(auto [i,j] : ans) {
        cout << i+1 << ' ' << j+1 << '\n';
    }
}
