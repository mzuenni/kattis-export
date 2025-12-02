#include <cmath>
#include <iostream>

const double PI = 4 * std::atan(1.0);

long gcd(long a, long b) {
  while (b > 0) {
    long t = a % b;
    a = b;
    b = t;
  }
  return a;
}

int main() {
  long n;
  std::cin >> n;

  long k = n / 2;
  long d = gcd(n, k);
  double v = n / d * sin((PI * k) / n);
  for (long i = k, j = d; j > 1; ) {
    --i;
    j = gcd(n, i);
    double u = n / j * sin((PI * i) / n);
    if (u > v) {
      k = i;
      d = j;
      v = u;
    }
  }

  std::cout << k << std::endl;

  return 0;
}
