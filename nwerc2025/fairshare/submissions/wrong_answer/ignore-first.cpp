#include <iostream>
#include <vector>
#include <numeric>
#include <cassert>

#define rep(a, b)   for(int a = 0; a < (b); ++a)
#define all(a)      begin(a),end(a)

using namespace std;
using ll = long long;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n; cin>>n;
    vector pay(n,0), owe(n,0);
    rep(i,n) cin>>pay[i] >> owe[i];
    auto total_bill = accumulate(all(owe), 0ll);
    auto total_paid = accumulate(all(pay), 0ll);

    int ans = -1;
    for(int i=1; i<n; ++i) {
        auto rem = total_bill - ll(total_paid - pay[i]);
        if(rem <= owe[i]) ans = i;
    }

    if(ans == -1) {
        cout << "impossible" << endl;
    } else {
        cout << ans+1 << endl;
    }

    return 0;
}
