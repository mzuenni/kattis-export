// Author: Stefan Toman
// This submission is wrong since it always prints exactly three significant
// figures instead of three decimal places.

#include <cmath>
#include <iostream>
#include <iomanip>

using namespace std;

main() {
  double x[3], y[3], r;
  for(int i = 0; i < 3; i++) {
    cin >> x[i] >> y[i];
  }
  cin >> r;
  double a[3], s = 0;
  for(int i = 0; i < 3; i++) {
    a[i] = sqrt(pow(x[i] - x[(i+1)%3], 2) + pow(y[i] - y[(i+1)%3], 2));
    s += a[i]/2;
  }
  double n = 1.0/sqrt(s);
  for(int i = 0; i < 3; i++) {
    n *= sqrt(s-a[i]);
  }
  cout << setprecision(3) << 100.0*(n-r)/r << endl;
}