#include <iostream>
#include <cstdlib>
using namespace std;

#define CASES  100
#define MAX    500

int main() {
  int i;
  cout << CASES << endl;
  for (i = 0; i < CASES; i++) {
    //  $j$, $p$, $H$, and $L$
    int j,p,H,L;
    p = 1 + (rand() % MAX);
    H = 1 + (rand() % MAX);
    j = 1 + (rand() % H);
    L = 1 + (rand() % MAX);
    cout << j << " " << p << " " << H << " " << L << endl;
  }
  return 0;
}
