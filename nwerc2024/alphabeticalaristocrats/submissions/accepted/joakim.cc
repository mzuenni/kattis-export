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
  vector<string> s(n);
  getline(cin,s[0]);
  rep(i,0,n) getline(cin,s[i]);
  auto cmp = [&](string a, string b) {
    return
      a.substr(find_if(all(a),[&](char c){return isupper(c);})-begin(a))
        <
      b.substr(find_if(all(b),[&](char c){return isupper(c);})-begin(b));
  };
  sort(all(s),cmp);
  for(auto a : s) cout << a << endl;
}
