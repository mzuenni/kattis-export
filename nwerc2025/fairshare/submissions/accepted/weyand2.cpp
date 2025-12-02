
#include <iostream>
#include <vector>
#include <numeric>
#include <cassert>
#include <algorithm>

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

    vector<int> ids(n);
    iota(all(ids),0);
    auto ans = *max_element(all(ids), [&](int i, int j) { return owe[i] - pay[i] < owe[j] - pay[j]; });
    auto total_bill = accumulate(all(owe), 0ll);
    auto total_paid = accumulate(all(pay), 0ll);

    if(total_paid - pay[ans] + owe[ans] >= total_bill) {
        cout << ans + 1 << endl;
    } else {
        cout << "impossible" << endl;
    }

    return 0;
}
