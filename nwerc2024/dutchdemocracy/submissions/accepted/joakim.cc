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
  vi v(n);
  rep(i,0,n) cin>>v[i];
  sort(rbegin(v),rend(v));
  int sm = accumulate(all(v),0);
  int need = sm/2+1;
  vector<ll> dp(1e6);
  dp[0] = 1;
  ll ans = 0;
  for(int x : v) {
    for(int t = need-1; t >= 0; --t) {
      dp[t+x] += dp[t];
      if(t+x >= need) ans += dp[t];
    }
  }
  cout << ans << endl;
}
