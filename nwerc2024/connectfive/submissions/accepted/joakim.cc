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
  vector<pii> v(5);
  for(auto& [x,y] : v) cin>>x>>y;
  vi rows, cols;
  for(auto [x,y] : v) rows.emplace_back(x), cols.emplace_back(y);
  sort(all(rows));
  sort(all(cols));
  rows.erase(unique(all(rows)), end(rows));
  cols.erase(unique(all(cols)), end(cols));
  int R = sz(rows), C = sz(cols);
  auto to_idx = [&](int x, auto& xs) { return lower_bound(all(xs), x) - begin(xs); };

  int K = R*(C-1) + C*(R-1);
  vi cost(K);
  auto right_of = [&](int i, int j) { return j*R+i; };
  auto below_of = [&](int i, int j) { return i*C+j + R*(C-1); };
  rep(i,0,R) rep(j,0,C-1)
    cost[right_of(i,j)] = cols[j+1]-cols[j];
  rep(i,0,R-1) rep(j,0,C)
    cost[below_of(i,j)] = rows[i+1]-rows[i];

  auto gen_path = [&](auto&& rec, int x0, int y0, int x1, int y1, ll msk, vector<ll>& pths) {
    if(x0 == x1 && y0 == y1) {
      pths.emplace_back(msk);
      return;
    }
    if(x0 < x1) rec(rec,x0+1,y0,x1,y1,msk|(1LL<<below_of(x0,y0)),pths);
    if(x0 > x1) rec(rec,x0-1,y0,x1,y1,msk|(1LL<<below_of(x0-1,y0)),pths);
    if(y0 < y1) rec(rec,x0,y0+1,x1,y1,msk|(1LL<<right_of(x0,y0)),pths);
    if(y0 > y1) rec(rec,x0,y0-1,x1,y1,msk|(1LL<<right_of(x0,y0-1)),pths);
  };
  vector<vector<ll>> pp;
  rep(i,0,5) rep(j,i+1,5) {
    pp.emplace_back();
    int x0 = to_idx(v[i].first,rows), y0 = to_idx(v[i].second,cols);
    int x1 = to_idx(v[j].first,rows), y1 = to_idx(v[j].second,cols);
    gen_path(gen_path,x0,y0,x1,y1,0,pp.back());
  }
  auto cost_of = [&](ll msk) {
    int res = 0;
    rep(i,0,K) if(msk>>i&1) res += cost[i];
    return res;
  };

  int best = 1e9;
  auto go_best = [&](auto&& rec, int i, ll msk) {
    if(cost_of(msk) >= best) return;
    if(i == sz(pp)) {
      best = cost_of(msk);
      return;
    }
    for(auto m : pp[i]) rec(rec, i+1, msk|m);
  };
  go_best(go_best,0,0);
  cout << best << endl;
}
