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
  ll n,k;
  cin>>n>>k;
  string s;
  cin>>s;

  vi p(n), z(n), pp(n);
  rep(i,0,n) p[i] = (2*i)%n, z[i] = i;
  while(k) {
    if(k&1) {
      rep(i,0,n) pp[i] = p[z[i]];
      swap(pp,z);
    }
    rep(i,0,n) pp[i] = p[p[i]];
    swap(pp,p);
    k /= 2;
  }
  rep(i,0,n) cout << s[z[i]];
  cout << endl;
}
