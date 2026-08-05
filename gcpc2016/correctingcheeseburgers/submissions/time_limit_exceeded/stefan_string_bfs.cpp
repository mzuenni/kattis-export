//Author: Stefan Toman

#include <iostream>
#include <unordered_set>
#include <string>

using namespace std;

//get all bit-shuffles of a set
unordered_set<string> step(int n, unordered_set<string> reachable, bool forward) {
  unordered_set<string> ret;
  for(auto it = reachable.begin(); it != reachable.end(); ++it) {
    for(int b = 0; b <= n; b++) {
      for(int c = b; c <= n; c++) {
        for(int d = c; d <= n; d++) {
          string pa = it->substr(0, b);
          string pb = it->substr(b, c-b);
          string pc = it->substr(c, d-c);
          string pd = it->substr(d, n-d);
          string p = forward ? pc + pa + pd + pb : pb + pd + pa + pc;
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
  int n, t;
  string start = "", end = "";
  cin >> n;
  for(int i = 0; i < n; i++) {
    cin >> t;
    start += to_string(t-1);
    end += to_string(i);
  }
  unordered_set<string> reachable_start ({start});
  
  //compute reachable nodes
  t = 0;
  while(reachable_start.find(end) == reachable_start.end()) {
    reachable_start = step(n, reachable_start, true);
    t++;
  }
  
  cout << t << endl;
  return 0;
}
