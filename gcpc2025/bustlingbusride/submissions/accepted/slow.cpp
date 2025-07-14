//
// Created by niko on 4/29/25.
//

#include <bits/stdc++.h>
#define rep(i,a,b) for (long long i = (a); i < (b); i++)

using namespace std;
using ll = long long;

int main() {
  int n, b;
  ll r, w;
  cin >> n >> b >> r >> w;
  vector<ll> d(b), t(n);
  rep(i, 0, b) cin >> d[i];
  rep(i, 1, b) d[i] += d[i-1];
  rep(i, 0, n) {
    int j;
    cin >> j, j--;
    t[i] = d[j];
  }

  auto cost = [&](int i, int len) -> ll {
    if (i + len > n) return 1e17;
    vector<ll> x(t.begin() + i, t.begin() + i + len);
    std::sort(x.begin(), x.end());

    ll c = x.back(); // driving cost

    // entry exit cost
    int entry_exits = 1;
    for (int i = 0; i < len; i++) {
      if (i > 0 && x[i-1] != x[i]) entry_exits++;
      c += 2 * w * entry_exits;
    }
    return c;
  };

  auto possible = [&](const ll m) -> bool {
    int i = 0;
    for (ll j = 0; i < n && j < m; j += r) {
      int hi = 1;
      while (j + cost(i, hi) <= m) hi *= 2;
      if (hi == 1) break;

      int lo = hi / 2;
      while (lo + 1 < hi) {
        int mi = std::midpoint(lo, hi);
        if (j + cost(i, mi) <= m) lo = mi;
        else hi = mi;
      }
      i += lo;
    }
    return i == n;
  };

  ll lo = 0, hi = n * (r + 2*w + *ranges::max_element(d));
  while (lo + 1 < hi) {
    ll mid = std::midpoint(lo, hi);
    if (possible(mid)) {
      hi = mid;
    } else {
      lo = mid;
    }
  }
  cout << hi << endl;
}
