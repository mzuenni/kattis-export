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

    long long n,k; cin>>n>>k;
    string s; cin>>s;

    vector x(n,0);
    rep(i,n) x[i] = 2*i%n;
    vector res(n,0);
    iota(all(res), 0);
    rep(b,63) {
        if(k & 1ll<<b) {
            // mul with x
            auto res2 = res;
            rep(i,n) res2[i] = x[res[i]];
            swap(res,res2);
        }
        // square x
        auto x2 = x;
        rep(i,n) x2[i] = x[x[i]];
        swap(x2,x);
    }
    rep(i,n) cout << s[res[i]];
    cout << endl;


    return 0;
}
