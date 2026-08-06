// @EXPECTED_RESULTS@: CORRECT
#include <iostream>
#include <string>
#include <vector>
#include <set>
#include <map>
#include <algorithm>
using namespace std;

typedef set<string>::iterator ssit;
typedef vector<string>::iterator vsit;
typedef map<string, set<string> >::iterator msit;

void tc() {
  map<string, set<string> >  T, R;
  set<string> A, B;
  int n;
  cin >> n;
  for (int i = 0; i < n; i++) {
    string p;
    cin >> p;
    int m;
    cin >> m;
    A.clear();
    for (int j = 0; j < m; j++) {
      string ing;
      cin >> ing;
      A.insert(ing);
    }
    cin >> m;
    B.clear();
    for (int j = 0; j < m; j++) {
      string ing;
      cin >> ing;
      B.insert(ing);
    }

    for (ssit a = A.begin(); a != A.end(); a++) {
      // empty -> any possible combination
      if (T.find(*a) == T.end()) {
        T[*a] = B;
      // non-empty -> filter out impossible solutions
      } else {
        vector<string> res(T[*a].size());
        set<string> x = T[*a];
        vsit end = set_intersection(x.begin(), x.end(), B.begin(), B.end(), res.begin());
        T[*a].clear();
        for (vsit r = res.begin(); r != end; r++) T[*a].insert(*r);
      }
    }

    for (ssit b = B.begin(); b != B.end(); b++) {
      // empty -> any possible combination
      if (R.find(*b) == R.end()) {
        R[*b] = A;
      // non-empty -> filter out impossible solutions
      } else {
        vector<string> res(R[*b].size());
        set<string> x = R[*b];
        vsit end = set_intersection(x.begin(), x.end(), A.begin(), A.end(), res.begin());
        R[*b].clear();
        for (vsit r = res.begin(); r != end; r++) R[*b].insert(*r);
      }
    }
  }

  for (msit t = T.begin(); t != T.end(); t++) {
    for (ssit b = t->second.begin(); b != t->second.end(); b++) {
      if (R[*b].find(t->first) != R[*b].end()) {
        cout << "(" << t->first << ", " << *b << ")" << endl;
      }
    }
  }
}

int main() {
  int ntc;
  cin >> ntc;
  while (ntc--) {
    tc();
    if (ntc) cout << endl;
  }
  return 0;
}
