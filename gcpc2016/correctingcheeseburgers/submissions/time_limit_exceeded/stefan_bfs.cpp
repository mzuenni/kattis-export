//Author: Stefan Toman

#include <iostream>
#include <unordered_set>
#include <vector>

using namespace std;

typedef long long ll;

//get all bit-shuffles of a set
unordered_set<ll> step(int n, unordered_set<ll> reachable, bool forward) {
  vector<ll> pow;
  ll t = 1;
  for(int i = 0; i <= n; i++) {
    pow.push_back(t);
    t *= n;
  }

  unordered_set<ll> ret;
  ll pa, pb, pc, pd, p;
  for(auto it = reachable.begin(); it != reachable.end(); ++it) {
    for(int b = 0; b <= n; b++) {
      for(int c = b; c <= n; c++) {
        for(int d = c; d <= n; d++) {
          t = *it;
          pd = t % pow[n-d];
          t /= pow[n-d];
          pc = t % pow[d-c];
          t /= pow[d-c];
          pb = t % pow[c-b];
          t /= pow[c-b];
          pa = t % pow[b];
          p = forward ? pa * pow[n-d + c-b] + pb + pc * pow[b + n-d + c-b] + pd * pow[c-b] : pa * pow[d-c] + pb * pow[n-d + b + d-c] + pc + pd * pow[d-c + b];
          if(ret.find(p) == ret.end()) {
            ret.insert(p);
          }
        }
      }
    }
  }

  return ret;
}

int main() {
  //read input
  ll n, t, start = 0, end = 0;
  cin >> n;
  for(int i = 0; i < n; i++) {
    cin >> t;
    start = start * n + (t-1);
    end = end * n + i;
  }
  unordered_set<ll> reachable_start ({start});
  
  //compute reachable nodes
  t = 0;
  while(reachable_start.find(end) == reachable_start.end()) {
    reachable_start = step(n, reachable_start, true);
    t++;
  }
                  
  cout << t << endl;
  return 0;
}
