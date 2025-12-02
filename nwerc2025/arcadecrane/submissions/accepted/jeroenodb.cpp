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
    int at = n;
    while(at>5) {
        if(a[at-1]==at-1) {
            at--;
            continue;
        }
        if(a[0]==at-1) {
            op(0,2);
        } else if(a[1]==at-1) {
            op(1,2);  
        }
        op(find(begin(a),end(a),at-1)-begin(a) -2, at-3);
    }
    while(!is_sorted(begin(a),end(a))) {
        while(at>0 and a[at-1]==at-1) {
            --at;
        }
        op(rnd(0,max(2,at-3)),rnd(0,max(2,at-3)));
    }

    cout << ans.size() << '\n';
    for(auto [i,j] : ans) {
        cout << i+1 << ' ' << j+1 << '\n';
    }
}
