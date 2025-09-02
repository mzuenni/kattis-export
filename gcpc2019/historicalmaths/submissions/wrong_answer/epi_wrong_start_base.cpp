#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using vl = vector<ll>;
#define sz(c) ll((c).size())
#define FOR(i,a,b) for(ll i = (a); i < (b); i++)
#define FORD(i,a,b) for(ll i = ll(b) - 1; i >= (a); i--)

void multiply(vl &a, vl &b, vl &res, ll base) {
  res.assign(sz(res), 0);
  FOR(i,0,sz(a)) {
    FOR(j,0,sz(b)) {
      res[i + j] += a[i] * b[j];
      res[i + j + 1] += res[i + j] / base;
      res[i + j] %= base;
    }
  }
  FOR(i,0,sz(res) - 1) {
    res[i + 1] += res[i] / base;
    res[i] %= base;
  }
}

ll compare(vl &a, vl &b) {
  if(sz(a) < sz(b)) {
    FOR(i,sz(a),sz(b)) if(b[i] != 0) return -1;
  }
  if(sz(a) > sz(b)) {
    FOR(i,sz(b), sz(a)) if(a[i] != 0) return 1;
  }
  FORD(i,0,min(sz(a),sz(b))) {
    if(a[i] - b[i] != 0) return a[i] - b[i];
  }
  return 0;
}

int main() {
	ios_base::sync_with_stdio(false);
  ll tmp, maxdigit = 2;
  cin >> tmp;
  vl a(tmp);
  FORD(i, 0, tmp) {cin >> a[i]; maxdigit = max(maxdigit, a[i]);};
  cin >> tmp;
  vl b(tmp);
  FORD(i, 0, tmp) {cin >> b[i]; maxdigit = max(maxdigit, b[i]);};
  cin >> tmp;
  vl prod(tmp);
  FORD(i, 0, tmp) {cin >> prod[i]; maxdigit = max(maxdigit, prod[i]);};
  vl res(sz(a) + sz(b) + 1);
  ll high = (2LL << 60) + 1, low = maxdigit - 1;
  bool possible = false;
  while(low + 1 < high) {
    ll base = (low + high)/2;
    multiply(a,b,res,base);
    ll cmp = compare(prod, res);
    if(cmp == 0) possible = true;
    if(cmp < 0) low = base;
    else high = base;
  }
  if(!possible)
    cout << "impossible" << endl;
  else
    cout << high << endl;
	return 0;
}
