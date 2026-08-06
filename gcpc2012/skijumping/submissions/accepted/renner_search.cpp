// @EXPECTED_RESULTS@: CORRECT
#include <iostream>
#include <iomanip>
#include <cmath>
using namespace std;

const double g = 9.81;
const double pi = 3.14159265358979;

double H, L, p, j;
double h(double l) {
  if (l < L/2) {
    return H * (1 - 2*(l/L)*(l/L));
  } else if (l < L) {
    return 2*H * (l/L - 1) * (l/L - 1);
  } else {
    return 0;
  }
}

double dh(double l) {
  if (l < L/2) {
    return -4*H*l/L/L;
  } else if (l < L) {
    return 4*H*(l/L - 1)/L;
  } else {
    return 0;
  }
}

double f(double l, double v0) {
  return H + p - g/2 * (l/v0) * (l/v0);
}

double df(double l, double v0) {
  return -g * l / v0 / v0;
}

double v(double l, double v0) {
  double vy = df(l, v0);
  return v0 * sqrt(vy*vy + 1);
}

double angle(double l, double v0) {
  double dfy, dhy;
  dhy = dh(l);
  dfy = df(l, v0);
  return 180.0 / pi * acos( (1 + dhy*dfy) / sqrt((1 + dhy*dhy) * (1 + dfy*dfy)));
}

void testcase() {
  cin >> j >> p >> H >> L;

  double v0 = sqrt(2*g*j);
  
  double l;
  double l_low = 0;
  double l_high = v0 * sqrt(2 * (H + p) / g); // f(l) = 0
  // find intersection
  do {
    l = (l_high + l_low) / 2;
    //cout << l << " -> " << f(l, v0) << " vs " << h(l) << endl;
    double gap = f(l, v0) - h(l);
    if (fabs(gap) <= 1e-10) break;
    if (gap > 0) {
      l_low = l;   // above ground, solution is to the right
    } else {
      l_high = l;  // below ground, solution is to the left
    }
  } while (l_high - l_low > 1e-10);

  cout << setprecision(15) << l <<" "<< v(l, v0) <<" "<< angle(l,v0) << endl;
}

int main() {
  int ntc;
  cin >> ntc;
  while (ntc--) testcase();
  return 0;
}
