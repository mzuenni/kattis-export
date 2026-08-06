// @EXPECTED_RESULTS@: CORRECT
#include <iostream>
#include <string>
#include <vector>
#include <set>
#include <map>
#include <algorithm>
using namespace std;

typedef vector<string>::iterator vsit;
typedef set<string>::iterator ssit;

void tc() {
  set<string> AA, BB;
  map<string, map<string, int> >  fCmb;
  map<string, int> fA, fB;
  vector<string> A, B;
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
      fA[ing]++;
      A.push_back(ing);
      AA.insert(ing);
    }
    cin >> m;
    B.clear();
    for (int j = 0; j < m; j++) {
      string ing;
      cin >> ing;
      fB[ing]++;
      B.push_back(ing);
      BB.insert(ing);
    }

    for (vsit a = A.begin(); a != A.end(); a++) {
      for (vsit b = B.begin(); b != B.end(); b++) {
        fCmb[*a][*b]++;
      }
    }
  }

  for (ssit a = AA.begin(); a != AA.end(); a++) {
    for (ssit b = BB.begin(); b != BB.end(); b++) {
      if (fA[*a] == fB[*b] && fA[*a] == fCmb[*a][*b]) {
        cout << "(" << *a << ", " << *b << ")" << endl;
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
