// @EXPECTED_RESULTS@: WRONG-ANSWER

#include <iostream>

#define abs(a) ((a > 0) ? (a) : (-a))

using namespace std;

#define BPM 50
#define B   20

int main() {
  int C;
  cin >> C;
  while (C--) {
    bool ok = true;
    int n;
    int x, y, x_old, y_old, d = 0;
    cin >> n;
    cin >> x >> y;
    for (int i = 1; i < n + 2; i++) {
      x_old = x; y_old = y;
      cin >> x >> y;
      d += abs( x - x_old ) + abs( y - y_old );
      if (d > B * BPM) ok = false;
      d %= BPM;
    }
    cout << (ok ? "happy" : "sad") << endl;
  }

  return 0;
}
