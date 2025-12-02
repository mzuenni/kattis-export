#include <cmath>
#include <iomanip>
#include <iostream>

const double HALF_OF_PI = 2 * std::atan(1.0);

int main() {
  double d;
  std::cin >> d;
  std::cout << std::setprecision(20) << HALF_OF_PI * d - d << std::endl;
  return 0;
}
