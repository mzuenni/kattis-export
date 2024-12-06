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

bool smin(auto &a, auto&& b) { return (b < a) ? (a = b, 1) : 0; } 
bool smax(auto &a, auto&& b) { return (a < b) ? (a = b, 1) : 0; } 

void bad(auto s) {
  cout << s << endl;
  exit(0);
}

int main() {
  cin.tie(0)->sync_with_stdio(0);
  cin.exceptions(cin.failbit);
  int n, m;
  cin>>n>>m;
  vi a(n);
  rep(i,0,n) cin>>a[i];
  vector<vi> g(2*n);
  rep(i,0,m) {
    int x,y;
    cin>>x>>y;
    --x,--y;
    int b = (a[x] == a[y] ? 1 : 0);
    g[2*x+b].emplace_back(2*y+1-b);
    g[2*y+b].emplace_back(2*x+1-b);
  }

  int q = 0;
  vi indeg(2*n), ord(2*n);
  rep(x,0,2*n) for(int y : g[x]) ++indeg[y];
  rep(x,0,2*n) if(indeg[x] == 0) ord[q++] = x;
  rep(i,0,2*n) {
    if(i >= q) bad("infinity");
    for(auto y : g[ord[i]]) if(--indeg[y] == 0) ord[q++] = y;
  }

  vi v = {0,1,1,0};
  int worst = 1e9;
  rep(t,0,4) {
    vi dp(2*n,0);
    for(int x : ord) {
      if(a[x/2] == v[t]) smax(dp[x],1);
      if(dp[x] > 0) for(int y : g[x]) {
        if(a[y/2] == v[(dp[x]+t)%4]) smax(dp[y],dp[x]+1);
      }
    }
    smin(worst, *max_element(all(dp)));
  }
  cout << 1+worst << endl;
}
