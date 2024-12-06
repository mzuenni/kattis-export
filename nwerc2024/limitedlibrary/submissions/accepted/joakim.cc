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


template<class I>
I bs(I a, I b, auto&& f) {
  assert(a < b);
  while(a + 1 < b) { // floats: s/1/eps
    I q = a + (b - a)/2;
    (f(q) ? b : a) = q;
  }
  return b;
}

int main() {
  cin.tie(0)->sync_with_stdio(0);
  cin.exceptions(cin.failbit);
  int n,m,x,y;
  cin>>n>>m>>x>>y;
  vi a(n),b(m);
  rep(i,0,n) cin>>a[i];
  rep(i,0,m) cin>>b[i];
  sort(rbegin(a),rend(a));
  sort(rbegin(b),rend(b));

  int q = bs(-1,n+1, [&](int k){
      vi slots(n);
      rep(i,0,n) slots[i] = i < n-k ? x : y;
      int i = 0;
      for(auto t : b) {
        if(slots[i] == 0) ++i;
        if(i == n) return true;
        if(a[i] < t) return true;
        debug(t,a[i])
        --slots[i];
      }
      return false;
  });
  --q;
  if(q == -1) cout << "impossible" <<  endl;
  else cout << q << endl;
}
