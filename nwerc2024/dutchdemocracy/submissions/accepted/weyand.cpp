#include <algorithm>
#include <iostream>
#include <iostream>
#include <numeric>
#include <vector>
#define rep(a, b)   for(int a = 0; a < (b); ++a)
#define all(a)      (a).begin(),(a).end()
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n; cin>>n;
    vector arr(n,0ll);
    rep(i,n) cin>>arr[i];
    sort(all(arr), greater<>());
    auto sum = accumulate(all(arr),0ll);

    vector cnts(sum+6, 0ll);
    cnts[0] = 1;
    int64_t ans = 0;
    for(auto c : arr) {
        for(int i=size(cnts)-1-c; i>=0; i--) {
            cnts[i+c] += cnts[i];
            if(2*(i+c) > sum && 2*i <= sum)
                ans += cnts[i];
        }
    }
    cout << ans << endl;

    return 0;
}
