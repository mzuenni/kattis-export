#include <bits/stdc++.h>
using namespace std;

#define rep(i, a, b) for(int i = a; i < (b); ++i)
#define all(x) begin(x), end(x)
#define sz(x) (int)(x).size()
#define debug(...) //ignore
typedef long long ll;
typedef pair<int, int> pii;
typedef vector<int> vi;
typedef long double ld;

int main() {
  cin.tie(0)->sync_with_stdio(0);
  cin.exceptions(cin.failbit);
  int n;
  cin>>n;
  vector<tuple<ll,ll,ll>> v(n);
  for(auto& [h,x,y] : v) cin>>x>>y>>h;
  rep(i,0,n) {
    ll close = 1e18;
    auto [h,x,y] = v[i];
    rep(j,0,n) {
      auto [hh,xx,yy] = v[j];
      if(hh > h) close = min((x-xx)*(x-xx)+(y-yy)*(y-yy),close);
    }
    while(h*h > close) --h;
    cout << h << endl;
  }
}
