// @EXPECTED_RESULTS@: CORRECT
#include <iostream>
#include <iomanip>
#include <cmath>
using namespace std;

typedef unsigned long ul;

const double g = 9.81;
const double pi = 3.14159265358979;

double vlen(double x, double y) {
  return sqrt( x*x + y*y );
}

void tc() {
  double l;
  double h, p, H, L;
  double dfx, dfy, dsx = 1.0, dsy, phi;

  cin >> h >> p >> H >> L;
  
  // get intersection with first part of hill
  double arg = 4.0*p / (1.0/h - 8.0*H/L/L);
  l = arg >= 0 ? sqrt(arg) : L;
  if (l <= L / 2.0) {
    // landing is in 1st
    dsy = -4.0*H*l/L/L;
  } else {
    // get intersection with second part of hill
    double a, b, c;
    a = 1.0/4/h + 2.0*H/L/L;
    b = -4.0*H/L;
    c = H-p;
    b = b / a;
    c = c / a;
    l = -b/2 + sqrt((b/2)*(b/2) - c); // solution cannot be -sqrt(.)

    if (l <= L) {
      // landing is in 2nd
      dsy = 4.0*H*(l/L-1)/L;
    } else {
      // landing is on plane
      l = sqrt( 4 * (H+p) * h ) ;
      dsy = 0;
    }
  }
  dfx = sqrt(2.0*g*h);
  dfy = -g*l/dfx;
  phi = 180 / pi * acos( (dfx*dsx + dfy*dsy) / (vlen(dfx,dfy) * vlen(dsx, dsy)) );
  cout << setprecision(15) << l << " " << vlen(dfx,dfy) << " " << phi << endl;
}


int main() {
  int ntc;
  cin >> ntc;
  while (ntc--) tc();
  return 0;
}
